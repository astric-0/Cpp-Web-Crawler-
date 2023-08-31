#include "../includes/Crawler.h"
#include <iostream>

class Spider : public Web :: Crawler {
    protected:
        Helpers :: CharList seedUrl;        
    public:
        Spider();
        Spider(Helpers :: CharList &);
        bool sendRequest();
        void autoExecute();
};

Spider :: Spider () {
    this->currQueue.deQ();
    this->seedUrl.assign("https://www.github.com/");
    this->currQueue.enQ(this->seedUrl);
}

Spider :: Spider (Helpers :: CharList &seedUrl) : Web :: Crawler (seedUrl) {
    this->seedUrl = seedUrl;
}

bool Spider :: sendRequest () {
    Url url(this->currQueue.deQ());

    Helpers::CharList domain;
    if(!url.getDomain(domain))
        return false;

    Helpers :: CharList cmd("curl ");
    cmd += url + " >> " + url + ".html";

    const int len = cmd.length();
    char cmdCharArr[len];
    cmd.fill(cmdCharArr, len);

    std :: cout << cmdCharArr << std :: endl << len;
    const bool isDownloaded = !system(cmdCharArr);
    return isDownloaded;  
}

void Spider :: autoExecute () {
        
}

int main() {
    Helpers :: CharList seedUrl("https://github.com");
    Spider spidy(seedUrl);

    //spidy.autoExecute();
    return 0;
}