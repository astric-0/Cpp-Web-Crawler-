#include <iostream>
#include "../../includes/Web/Backgrounds.h"
#include "../../includes/Web/Url.h"

int main () {    
    Web :: Url url("https://www.google.com");        

    Helpers :: CharList domain;
    domain = "domain";
    std :: cout << "BEFORE: " << domain << std :: endl;
    bool flag = url.getDomain(domain);
    
    //std :: cout << flag << std :: endl;
    std :: cout << url << std :: endl;
    std :: cout << domain << std :: endl;

    Web :: Backgrounds :: init(domain);

    Helpers :: CharList filename = "xyz.html";
    Helpers :: Queue urlsQueue;
    bool isOk = Web :: Backgrounds :: filterURLs(filename);

    if (isOk) {
        Web :: Backgrounds :: fillNewURLs(urlsQueue);
        //std :: cout << urlsQueue;
    }
    else
        std :: cout << "failed";

    return 0;
}