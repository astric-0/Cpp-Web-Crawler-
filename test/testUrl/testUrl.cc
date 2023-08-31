#include "../../includes/Web/Url.h"
#include <iostream>

void foo (Helpers::CharList &domain) {
    std :: cout << "WORKED:: " << domain << std :: endl;
}

int main() {
    Web:: Url urlValue;
    urlValue = "https://www.google.com";    
    
    Helpers :: CharList domainName;
    bool flag = urlValue.getDomain(domainName);    

    if (flag)
        std :: cout << domainName << std :: endl;
    else
        std :: cout << "FAILED" << std :: endl;

    return 0;
}