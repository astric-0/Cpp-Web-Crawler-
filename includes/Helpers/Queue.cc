#include "Queue.h"
#include <cstdlib>
#include <iostream>

namespace Helpers {

    std :: ostream& operator<< (std :: ostream &ostreamObj, const Queue &queueObj) {
        if (queueObj.start == NULL)            
            return ostreamObj;        

        QueueNode *queueObjStart = queueObj.start;                
        while (queueObjStart != nullptr) {            
            ostreamObj << queueObjStart->str << '\n';
            queueObjStart = queueObjStart->next;
        }
        
        return ostreamObj;
    }
}

void Helpers :: QueueNode :: add (const CharList &charListObj) {
    this->str.assign(charListObj);
    this->next = NULL;
}

void Helpers :: Queue :: init () {
    this->start = NULL;
    this->end = NULL;
    this->len = 0;
}

Helpers :: Queue :: Queue () {
    this->init();
}

Helpers :: Queue :: Queue (Helpers :: Queue &queueObj) {
    this->init();
    this->extendQ(queueObj);
}

Helpers :: Queue :: ~Queue () {
    this->deleteQueue();
}

void Helpers :: Queue :: deleteQueue () {
    if (this->start == NULL) return;

    Helpers :: QueueNode *currNode = this->start;
    Helpers :: QueueNode *currEnd = this->end;
    Helpers :: QueueNode *temp = nullptr;
    while (currNode) {
        temp = currNode->next;        
        free(currNode);        
        currNode = temp;
    }

    this->start = nullptr;
    this->end = nullptr;
    this->len = 0;
}

void Helpers :: Queue :: enQ (CharList &charListObj) {
    if (charListObj.length() == 0) return;

    QueueNode *temp = new QueueNode();
    temp->add(charListObj);   

    if(this->start == NULL){
        this->start = temp;
        this->end = temp;
        this->len++;
        return;
    }

    this->end->next = temp;
    this->end = temp;
    this->len++;
}

Helpers :: CharList Helpers :: Queue :: deQ () {
    CharList tempCharListObj;
    if (this->start == NULL) return tempCharListObj;

    QueueNode *temp = this->start->next;
    tempCharListObj =this->start->str;
    
    delete this->start;
    this->start = temp;
    this->len--;

    return tempCharListObj;
}

void Helpers :: Queue :: extendQ (Helpers :: Queue &queueObj) {
    if(queueObj.start == NULL)  return;

    Helpers :: QueueNode *queueObjCurr = queueObj.start;
    Helpers :: QueueNode *queueObjEnd = queueObj.end;

    while (queueObjCurr != queueObjEnd->next) {
        this->enQ(queueObjCurr->str);
        queueObjCurr = queueObjCurr->next;
    }
}

unsigned int Helpers :: Queue :: length () {
    return this->len;
}

void Helpers :: Queue :: operator= (Helpers :: Queue &queueObj) {
    this->deleteQueue();
    this->init();
    this->extendQ(queueObj);
}