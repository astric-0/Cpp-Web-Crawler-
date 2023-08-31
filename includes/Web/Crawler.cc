#include <iostream>
#include <unistd.h>
#include <libxml/HTMLparser.h>

#include "Crawler.h"
#include "Session.h"
#include "Url.h"
#include "Backgrounds.h"

#include "../Utils/Args.h"
#include "../Utils/DateString.h"
#include "../Utils/Dir.h"

bool Web :: Crawler :: sendRequest (Helpers :: CharList &url, Helpers :: CharList &filename) {
    Helpers :: CharList cmd ("(curl ");
    cmd += url + " >> " + filename + ") > /dev/null 2>&1";

    const int len = cmd.length();
    char cmdCharArr[len];
    cmd.fill (cmdCharArr, len);

    const bool isDownloaded = !system(cmdCharArr);
    return isDownloaded;
}

void Web :: Crawler :: execute (int key) {

    const int MAX_SLEEP_TIME = 6;
    const int MAX_LEVEL = 2;

    this->sessions[key]->print();
    std :: cout << std :: endl;
    Helpers :: CharList sessionName = this->sessions[key]->getName();

    while (true) {
        int currCount = this->sessions[key]->getCount();        
        int currLevel = this->sessions[key]->getLevel();

        if (!this->sessions[key]->currQueueLength() && !this->sessions[key]->nextQueueLength() || currLevel >= MAX_LEVEL)
            break;

        Helpers :: CharList filename, domain;
        Web :: Url currUrl;
        currUrl = this->sessions[key]->deCurrQ();

        if (currUrl.length() == 0) continue;

        currUrl.getDomain(domain);
        Helpers :: CharList hostUrl("https://");
        hostUrl += domain;

        std :: cout << std :: endl << std :: endl;
        std :: cout << "URL : " << currUrl << std :: endl;        
        std :: cout << "LEVEL : [ " << currLevel << " ] [ " << currCount << " ]" << std :: endl;

        std :: cout << "P [ " << this->sessions[key]->currQueueLength() << " ] " << std :: endl;
        std :: cout << "C [ " << this->sessions[key]->nextQueueLength() << " ] " << std :: endl;        

        Helpers :: CharList dirs[2], preset ("./");
        preset.append(sessionName);
        preset.append('/');
        dirs[0] = domain;
        dirs[1] = dirs[1] + currLevel;
        Utils :: Dir :: makeDirRecusive(preset, dirs, 2);

        Web :: Backgrounds :: init(hostUrl, this->sessions[key]->visited);

        Helpers :: CharList currLevelList;
        currLevelList = currLevelList + currLevel;
        Helpers :: CharList countList;
        countList = countList + currCount;

        filename.assign(preset);
        filename.append(domain);
        filename.append('/');
        filename.append(currLevelList);
        filename.append('/');
        filename.append(countList);
        filename.append(".html");

        unsigned long before = Utils :: DateString :: getCurrMilliSeconds();
        if (this->sendRequest(currUrl, filename)) {
            this->sessions[key]->visited.push(currUrl.getId());

            std :: cout << "SUCCESS" << std :: endl;
            if (Web :: Backgrounds :: filterURLs(filename)) {
                std :: cout << "LINKS FILTERED : " << Web :: Backgrounds :: newURLsLength() << std :: endl;

                Helpers :: Queue newURLsObj;
                Web :: Backgrounds :: fillNewURLs(newURLsObj);                
                this->sessions[key]->extendNextQ(newURLsObj);

                newURLsObj.deleteQueue();
                this->sessions[key]->visited = Web :: Backgrounds :: getTracker();
                this->sessions[key]->saveVisited();
            }
            else 
                std :: cout << "COULDN'T FILTER URLS" << std :: endl;
        }
        else
            std :: cout << "REQUEST FAILED" << std :: endl;

        Web :: Backgrounds :: reset();

        if (this->sessions[key]->currQueueLength() == 0) {
            std :: cout << "LEVELED UP" << std :: endl;
            this->sessions[key]->levelUp();
            this->sessions[key]->saveCurrLevel();
        }

        this->sessions[key]->saveQueues();

        std :: cout << "TRACKER SIZE : " << this->sessions[key]->visited.getSize() << std :: endl;
        unsigned long after = Utils :: DateString :: getCurrMilliSeconds();        
        int timeSpent = after - before;
        int sleepTime = (MAX_SLEEP_TIME - timeSpent);        
        std :: cout << std :: endl << "SLEEPING FOR : " << sleepTime << std :: endl;
        usleep(sleepTime * 1000000);

        this->sessions[key]->increaseCount();
        this->sessions[key]->saveCurrCount();
    }

    std :: cout << "QUEUES ARE EMPTY" << std :: endl;
}

int Web :: Crawler :: createSession () {
    int count = this->sessionCount;
    this->sessions[count] = new Session ();
    this->sessionCount++;
    return this->sessionCount-1;
}

int Web :: Crawler :: createSession (int argc, char* argv[]) {
    int count = this->sessionCount;
    this->sessions[count] = new Session (argc, argv);
    this->sessionCount++;
    return this->sessionCount-1;
}

bool Web :: Crawler :: deleteSession (int key) {
    delete this->sessions[key];
    this->sessions[key] = nullptr;
    return true;
}