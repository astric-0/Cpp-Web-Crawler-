#include <iostream>
#include "Backgrounds.h"
#include "Tracker.h"

Helpers :: Queue Web :: Backgrounds :: newURLs;
Helpers :: CharList Web :: Backgrounds :: hostUrl;
Web :: Tracker Web :: Backgrounds :: tracker;

void Web :: Backgrounds :: init (Helpers :: CharList &hostUrlObj, Tracker &t) {
    Web :: Backgrounds :: reset();
    Web :: Backgrounds :: hostUrl.assign(hostUrlObj);    
    Web :: Backgrounds :: tracker = t;
}

void Web :: Backgrounds :: reset () {    
    Web :: Backgrounds :: newURLs.deleteQueue();
    Web :: Backgrounds :: hostUrl.deleteCharList();
    Web :: Backgrounds :: tracker.deleteTracker();    
}

void Web :: Backgrounds :: nodeTraverser (xmlNode *node) {
    xmlNode *curNode = NULL;
    for (curNode = node; curNode; curNode = curNode->next) {
        if (curNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(curNode->name, (const xmlChar *)"a") == 0) {
                char *charPtrLink = (char*) xmlGetProp(curNode, (const xmlChar *)"href");

                if (charPtrLink != NULL) {
                    Helpers :: CharList url (charPtrLink);   
                    Helpers :: CharList toFind("http");

                    if (url.find(toFind) == -1)
                        url = Web :: Backgrounds :: hostUrl + "/" + url;

                    xmlFree(charPtrLink);
                    long id = url.getId();
                    int index = Backgrounds :: tracker.push(id);
                    if (index != -1)
                        Web :: Backgrounds :: newURLs.enQ(url);
                }
            }
        }
        nodeTraverser (curNode->children);
    }
}

Web :: Tracker Web :: Backgrounds :: getTracker () {
    return Web :: Backgrounds :: tracker;
}

bool Web :: Backgrounds :: filterURLs (Helpers :: CharList &filename) {
    xmlDocPtr doc;
    xmlNode* root;

    const int len = filename.length();
    char charArrFileName[len];
    filename.fill(charArrFileName, len);

    doc = htmlReadFile(charArrFileName , nullptr, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
    if (doc == nullptr) {
        //std :: cerr << "Error parsing the document." << std::endl;
        return false;
    }

    root = xmlDocGetRootElement(doc);
    if (root == nullptr) {
        //std :: cerr << "Empty document." << std::endl;
        xmlFreeDoc(doc);
        return false;
    }

    Web :: Backgrounds :: nodeTraverser(root);
    xmlFreeDoc(doc);
    return true;
}

void Web :: Backgrounds :: fillNewURLs (Helpers :: Queue &urlsQueueObj) {    
    urlsQueueObj.extendQ(Web :: Backgrounds :: newURLs);
    //this->reset();
}

int Web :: Backgrounds :: newURLsLength () {
    return Web :: Backgrounds :: newURLs.length();
}