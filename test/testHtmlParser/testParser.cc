#include <iostream>
#include <libxml/HTMLparser.h>

void printTags(xmlNode* node) {
    for (xmlNode* curNode = node; curNode; curNode = curNode->next) {
        if (curNode->type == XML_ELEMENT_NODE) {
            std::cout << "Tag: " << curNode->name << std::endl;            
        }
        printTags(curNode->children);
    }
}

void extractAnchorLinks(xmlNode *node) {
    xmlNode *curNode = NULL;
    for (curNode = node; curNode; curNode = curNode->next) {
        if (curNode->type == XML_ELEMENT_NODE) {
            if (xmlStrcmp(curNode->name, (const xmlChar *)"a") == 0) {
                xmlChar *link = xmlGetProp(curNode, (const xmlChar *)"href");
                if (link != NULL) {
                    std::cout << "Link: " << link << std::endl;
                    xmlFree(link);
                }
            }
        }
        extractAnchorLinks(curNode->children);
    }
}

int main() {
    xmlDocPtr doc;
    xmlNode* root;

    doc = htmlReadFile("abc.html", nullptr, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
    if (doc == nullptr) {
        std::cerr << "Error parsing the document." << std::endl;
        return 1;
    }

    root = xmlDocGetRootElement(doc);
    if (root == nullptr) {
        std::cerr << "Empty document." << std::endl;
        xmlFreeDoc(doc);
        return 1;
    }
    
    extractAnchorLinks(root);

    xmlFreeDoc(doc);
    return 0;
}

//g++ -Wall -lxml2 ./testParser.cc 