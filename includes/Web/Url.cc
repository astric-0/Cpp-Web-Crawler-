#include "Url.h"

Web :: Url :: Url () : Helpers :: CharList () {}
Web :: Url :: Url (const char *urlCharArr) : Helpers :: CharList (urlCharArr) { }
Web :: Url :: Url (const Helpers :: CharList &urlCharList) : Helpers :: CharList (urlCharList) {}

bool Web :: Url :: getDomain (Helpers :: CharList &domainObj) {
    if (this->start == NULL) return false;

    Helpers :: CharNode *currChar = this->start;

    char find[4] = "://";
    int i = 0;    

    while (currChar != NULL && i < 3) {                
        if (currChar->ch == find[i])
            i++;
        else i = 0;
        currChar = currChar->next;
    }

    if (currChar == NULL) return false;    
    if (i == 3) {        
        while (currChar && currChar->ch != '/') {            
            Helpers :: CharNode node;
            node.ch = currChar->ch;
            node.next = NULL;
            domainObj.append(node);
            currChar = currChar->next;            
        }
    }

    return true;
}