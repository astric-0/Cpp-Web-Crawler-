#include <fstream>
#include <ostream>
#include "Session.h"
#include "../Utils/DateString.h"
#include "../Utils/Args.h"
#include "../Utils/Dir.h"
#include "Tracker.h"

Web :: Session :: Session () {

    this->sessionData.name = Utils :: DateString :: getCurrentDateTimeString();
    this->sessionData.seedUrl = Web :: DEFAULT_URL;
    this->sessionData.currQueue.enQ(this->sessionData.seedUrl);    
    this->sessionData.currLevel = 0;
    this->sessionData.count = 0;

    Utils :: Dir :: makeDir (this->sessionData.name);
}

Web :: Session :: Session (int argc, char* argv[]) {
    Utils :: Args argsObj (argc, argv);

    Helpers :: CharList resumeFile (argsObj.getArg('r'));    
    std :: cout << "RESUMING FILE : " << resumeFile << std :: endl;
    if (resumeFile.length() != 0) {
        std :: cout << "RESUMING : " << resumeFile << std :: endl;
        this->sessionData.name = resumeFile;
        this->resume();        
    }
    else {
        Helpers :: CharList name (argsObj.getArg('s')); 
        if (!name.length())
            this->sessionData.name = Utils :: DateString :: getCurrentDateTimeString();
        else 
            this->sessionData.name = name;
        this->sessionData.seedUrl = Web :: DEFAULT_URL;
        this->sessionData.currQueue.enQ(this->sessionData.seedUrl);
        this->sessionData.currLevel = 0;
        this->sessionData.count = 0;
        Utils :: Dir :: makeDir (this->sessionData.name);
    }
}

void Web :: Session :: qReader (Helpers :: CharList &filename, Helpers :: Queue &que) {
    
    int size = filename.length();
    char filenameChar[size];
    filename.fill(filenameChar, size);

    std :: ifstream fileObj;
    fileObj.open(filenameChar, std :: ios :: in);

    Helpers :: CharList singleUrl;
    char ch;
    while (fileObj >> std :: noskipws >> ch) {
        if (ch == '\n') {
            que.enQ(singleUrl);
            singleUrl.deleteCharList();
            continue;
        }
        singleUrl.append(ch);
    }    
}

int Web :: Session :: iReader (Helpers :: CharList &filename) {    

    int size = filename.length();
    char filenameChar[size];
    filename.fill(filenameChar, size);    
    
    std :: ifstream fileObj;
    fileObj.open(filenameChar, std :: ios :: in);
    
    int num = 0;
    while (fileObj >> num);
    fileObj.close();

    return num;
}

void Web :: Session :: vReader (const Helpers :: CharList &dirname, Tracker &tObj) {
    Helpers :: CharList visitedFile (dirname);
    visitedFile.append(Web :: VISITED_FILENAME);

    std :: ifstream fObj;
    int size = visitedFile.length();
    char visitedFileChar[size];
    visitedFile.fill(visitedFileChar, size);

    fObj.open(visitedFileChar, std :: ios :: in);    
    long num;
    while (fObj >> num)
        tObj.push(num);
    fObj.close();
}

void Web :: Session :: saveQueues () {

    Helpers :: CharList dirname(this->sessionData.name);
    Helpers :: CharList currQueueFile, nextQueueFile;    

    currQueueFile.assign(dirname);    
    currQueueFile.append(Web :: CURR_QUEUE_FILE_NAME);

    nextQueueFile.assign(dirname);
    nextQueueFile.append(Web :: NEXT_QUEUE_FILE_NAME);

    int cSize = currQueueFile.length();
    int nSize = nextQueueFile.length();

    char currQueueFileChar[cSize];
    char nextQueueFileChar[nSize];

    currQueueFile.fill(currQueueFileChar, cSize);    
    nextQueueFile.fill(nextQueueFileChar, nSize);    

    std :: ofstream fileObj;

    fileObj.open(currQueueFileChar, std :: ios :: trunc);
    fileObj << this->sessionData.currQueue;
    fileObj.close();

    fileObj.open(nextQueueFileChar, std :: ios :: trunc);
    fileObj << this->sessionData.nextQueue;
    fileObj.close();
}

void Web :: Session :: saveFileName () {
    std :: ofstream fileObj;
    Helpers :: CharList dirname(this->sessionData.name);

    Helpers :: CharList sessionNameFile (dirname);    
    sessionNameFile.append(Web :: SESSION_FILENAME);

    int size = sessionNameFile.length();
    char sessionNameFileChar[size];
    sessionNameFile.fill(sessionNameFileChar, size);

    fileObj.open(sessionNameFileChar, std :: ios :: trunc);
    fileObj << dirname;
    fileObj.close();    
}

void Web :: Session :: saveCurrLevel () {
     std :: ofstream fileObj;
    Helpers :: CharList dirname(this->sessionData.name);

    Helpers :: CharList currLevelFile (dirname);    
    currLevelFile.append(Web :: LEVEL_FILE_NAME);

    int size = currLevelFile.length();
    char currLevelFileChar[size];
    currLevelFile.fill(currLevelFileChar, size);

    fileObj.open(currLevelFileChar, std :: ios :: trunc);
    fileObj << this->sessionData.currLevel;
    fileObj.close(); 
}

void Web :: Session :: saveCurrCount () {
    std :: ofstream fileObj;
    Helpers :: CharList dirname(this->sessionData.name);

    Helpers :: CharList currCountFile (dirname);    
    currCountFile.append(Web :: COUNT_FILE_NAME);

    int size = currCountFile.length();
    char currCountFileChar[size];
    currCountFile.fill(currCountFileChar, size);

    fileObj.open(currCountFileChar, std :: ios :: trunc);
    fileObj << this->sessionData.count;
    fileObj.close(); 
}

void Web :: Session :: saveVisited () {
    std :: ofstream fileObj;
    Helpers :: CharList dirname (this->sessionData.name);

    Helpers :: CharList visitedFile (dirname);
    visitedFile.append(Web :: VISITED_FILENAME);

    int size = visitedFile.length();
    char visitedFileChar[size];
    visitedFile.fill(visitedFileChar, size);

    fileObj.open(visitedFileChar, std :: ios :: trunc);
    fileObj << this->visited;
    fileObj.close();
}

void Web :: Session :: resume () {
    Helpers :: CharList dirname(this->sessionData.name);
    Helpers :: CharList currQueueFile (dirname), nextQueueFile (dirname);    
    
    currQueueFile.append(Web :: CURR_QUEUE_FILE_NAME);    
    nextQueueFile.append(Web :: NEXT_QUEUE_FILE_NAME);

    Session :: qReader(currQueueFile, this->sessionData.currQueue);
    Session :: qReader(nextQueueFile, this->sessionData.nextQueue);

    Helpers :: CharList countFile(dirname), levelFile(dirname);

    countFile.append(Web :: COUNT_FILE_NAME);
    levelFile.append(Web :: LEVEL_FILE_NAME);    

    this->sessionData.count = Session :: iReader(countFile);
    this->sessionData.currLevel = Session :: iReader(levelFile);
    Session :: vReader(this->sessionData.name, this->visited);
}

Helpers :: CharList Web :: Session :: deCurrQ () {
    return this->sessionData.currQueue.deQ();
}

void Web :: Session :: extendNextQ (Helpers :: Queue &queueObj) {
    this->sessionData.nextQueue.extendQ(queueObj);
}

void Web :: Session :: levelUp () {
    this->sessionData.currQueue.deleteQueue();
    this->sessionData.currQueue.extendQ(this->sessionData.nextQueue);
    this->sessionData.nextQueue.deleteQueue();
    this->sessionData.currLevel++;
}

int Web :: Session :: getLevel () {
    return this->sessionData.currLevel;
}

int Web :: Session :: currQueueLength () {
    return this->sessionData.currQueue.length();
}

int Web :: Session :: nextQueueLength () {
    return this->sessionData.nextQueue.length();
}

void Web :: Session :: print () {
    std :: cout << "SESSION NAME: " << this->sessionData.name << std :: endl;
    std :: cout << "CURRENT LEVEL: " << this->sessionData.currLevel << std :: endl;
    std :: cout << "CURRENT COUNT: " << this->sessionData.count << std :: endl;
    std :: cout << "CURR QUEUE: " << this->sessionData.currQueue << std :: endl;
    std :: cout << "NEXT QUEUE: " << this->sessionData.nextQueue << std :: endl;
}

void Web :: Session :: increaseCount () {
    this->sessionData.count++;
}

int Web :: Session :: getCount () {
    return this->sessionData.count;
}

Helpers :: CharList Web :: Session :: getName () {
    return this->sessionData.name;
}