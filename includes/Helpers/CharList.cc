#include "CharList.h"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace Helpers {
    std :: ostream& operator<<(std::ostream &ostreamObj, CharList charListObj) {

        if(charListObj.start == NULL)
            return ostreamObj << "[ EMPTY ]";        

        CharNode *currNodePtr = charListObj.start;
        while(currNodePtr != NULL) {
            ostreamObj << currNodePtr->ch;
            currNodePtr = currNodePtr->next;
        }

        return ostreamObj;
    }
};

void Helpers :: CharList :: setId () {
    if (this->start == nullptr) return;
    this->id = 0;
    int i = 0;
    CharNode *temp = this->start;    
    while (temp) {            
        id += i | temp->ch;
        temp = temp->next;
        i++;
    }
}

void Helpers :: CharList :: init () {
    this->start = NULL;
  	this->end = NULL;
  	this->len = 0;
    this->id = 0;
    this->isShallowCopy = false;    
}

void Helpers :: CharList :: forceInit () {
    this->start = new CharNode();
    this->end = this->start;    
}

Helpers :: CharList :: CharList () {
  	this->init();
}

Helpers :: CharList :: CharList (const char *charArrPtr) {
    this->init();
    this->assign(charArrPtr);
}

Helpers :: CharList :: CharList (const CharList &charListObj) {
    this->init();
    this->assign(charListObj);
}

Helpers :: CharList :: ~CharList () {  
    this->deleteCharList();    
}

bool Helpers :: CharList :: fill (char *ch, int size) {
  	if (this->start == NULL) return false;

	CharNode *currPtr = this->start;
	int i = 0, count = 0;
	while (count <= size) {
		if (currPtr == NULL) break;
        if (currPtr->ch == '\0') {
            currPtr = currPtr->next;
            count++;
            continue;
        }
		ch[i] = currPtr->ch;
		currPtr = currPtr->next;
        count++;
        i++;
	}

	ch[i] = '\0';
    return true;
}

bool Helpers :: CharList :: isShallow () { return this->isShallowCopy; }

int Helpers :: CharList :: length () { return this->len; }

void Helpers :: CharList :: assign (const char *charArr) {

    if (charArr[0] == '\0') return;
  	int i = 0;
  	CharNode *temp = NULL, *currPtr = NULL;    

  	if (this->start != NULL) this->deleteCharList();
    
	currPtr = new CharNode();
	currPtr->ch = charArr[i];
	currPtr->next = NULL;
	this->start = currPtr;
    i++;
    //std :: cout << this->id << ":" << i << ":" << charArr[i] << std :: endl;
    //this->id += i | charArr[i];    
	while (charArr[i] ) {
        
		temp = new CharNode();
		temp->ch = charArr[i];
		temp->next = NULL;

        //std :: cout << this->id << ":" << i << ":" << charArr[i] << std :: endl;
        //this->id += i | charArr[i];        

		currPtr->next = temp;
		currPtr = temp;
        i++;
	}
    this->len = i;
	this->end = currPtr;

    this->setId();
}

void Helpers :: CharList :: assign (const CharList &charListObj) {
	CharNode *charListObjStart = charListObj.start;
	CharNode *charListObjEnd = charListObj.end;     

	if (charListObjStart == NULL) return;
    if (this->start == charListObjStart) return;

	if (this->start != NULL) {
		if(!this->deleteCharList())
            return;
    }

    CharNode *currPtr = new CharNode();
	currPtr->ch = charListObjStart->ch;
	currPtr->next = nullptr;
	this->start = currPtr;

	charListObjStart = charListObjStart->next;

	while (charListObjStart) {
		CharNode *temp = new CharNode();        
		temp->ch = charListObjStart->ch;
		temp->next = nullptr;
		currPtr->next = temp;
		currPtr = temp;

		charListObjStart = charListObjStart->next;
        this->len++;
	}

    this->len++;
	this->end = currPtr;
    this->setId();    
}

void Helpers :: CharList :: append (const char *buffer, int size) {
    if(size == 0) return;    
    if(this->start == NULL) this->forceInit();

    CharNode *currEnd = this->end;
    int i = 0;
    while (i < size || (size == -1 && buffer[i] != '\0')) {
        CharNode *temp = new CharNode();        
        temp->ch = buffer[i];
        temp->next = NULL;        

        currEnd->next = temp;
        currEnd = temp;
        i++;
        this->len++;
    }

    this->end = currEnd;
    this->setId();
}

void Helpers :: CharList :: append (const CharList &charListObj) {
    if (charListObj.start == NULL) return;
    if (this->start == NULL) this->forceInit();

    CharNode *charListObjStart = charListObj.start;
    CharNode *charListObjEnd = charListObj.end;
    CharNode *currEnd = this->end;

    while (charListObjStart != charListObjEnd->next) {
        CharNode *temp = new CharNode();
        temp->ch = charListObjStart->ch;
        temp->next = NULL;

        currEnd->next = temp;
        currEnd = temp;
        this->len++;
        charListObjStart = charListObjStart->next;
    }
    
    this->end = currEnd;
    this->setId();
}

void Helpers :: CharList :: append (const CharNode &charNode) {
    if (charNode.ch == '\0') return;

    CharNode *temp = new CharNode();    
    temp->ch = charNode.ch;
    temp->next = NULL;

    if (this->start == NULL) { 
        this->start = temp;
        this->end = temp;
        return;
    };

    this->end->next = temp;
    this->end = temp;
    this->len++;

    this->setId();
}

void Helpers :: CharList :: append (const char &ch) {
    if (ch == '\0') return;

    CharNode *temp = new CharNode();    
    temp->ch = ch;
    temp->next = NULL;

    if (this->start == NULL) { 
        this->start = temp;
        this->end = temp;
        return;
    };

    this->end->next = temp;
    this->end = temp;
    this->len++;

    this->setId();
}

int Helpers :: CharList :: find (const char ch) {
    if (this->start == NULL) return -1;    
    if (ch == '\0') return -1;

    int i = 0;
    for (Helpers :: CharNode *currNode = this->start; currNode != NULL; currNode = currNode->next) {        
        if (currNode->ch == ch)
            return i;
        i++;
    }

    return -1;
}

int Helpers :: CharList :: find (const CharList &charListObj) {
    if (this->start == NULL) return -1;
    if (charListObj.start == NULL) return -1;

    bool check = false;
    int i = 0, index = -1;
    CharNode *objCurr = charListObj.start;    
    CharNode *currNode = this->start;    
    while (currNode != NULL && objCurr != NULL) {
        if (currNode->ch == objCurr->ch) {        
            !check && (index = i);
            check = true;
            objCurr = objCurr->next;
        }
        else {
            check = false;
            objCurr = charListObj.start;
        }
        currNode = currNode->next;        
        i++;
    }

    return (objCurr == NULL && check) ? index : -1;
}

unsigned long Helpers :: CharList :: getId () {
    return this->id;
}

bool Helpers :: CharList :: deleteCharList () {	
    if (this->isShallow()) {
        throw std :: runtime_error("Can't delete shallow copy");    
        return false;
    }

    if (this->start == NULL) return false;

    CharNode *curr = this->start;
    CharNode *next;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
    this->init();
    return true;    
}

void Helpers :: CharList :: print () {
	if (this->start == NULL) return;

	CharNode *start = this->start;	
	while (start) {
		std :: cout << start->ch;
		start = start->next;
	}
}

void Helpers :: CharList :: makeShallowCopy (const CharList &charListObj) {
    if(charListObj.start == NULL) return;
    if (this->start == charListObj.start) return;
    if (this->start != NULL) this->deleteCharList();

    this->isShallowCopy = true;

    this->start = charListObj.start;
    this->end = charListObj.end;
    this->len = charListObj.len;
}

Helpers :: CharList Helpers :: CharList :: operator= (const CharList &charListObj) {    
    this->assign(charListObj);    
    return *this;
}

Helpers :: CharList Helpers :: CharList :: operator= (const char *charArr) {    
    this->assign(charArr);
    return *this;
}

void Helpers :: CharList :: operator+= (const CharList &charListObj) {
    this->append(charListObj);
}

Helpers :: CharList Helpers :: CharList :: operator+ (const CharList &charListObj) {
    Helpers :: CharList result;

    if (this->start == NULL && charListObj.start == NULL)
        return result;

    else if (this->start == NULL && charListObj.start != NULL) {
        result.assign(charListObj);
        return result;
    }

    else if (this->start != NULL && charListObj.start == NULL) {
        result.assign(*this);
        return result;
    }

    result.assign(*this);
    result.append(charListObj);

    return result;
}

Helpers :: CharList Helpers :: CharList :: operator+ (const char *charArr) {    
    Helpers :: CharList result("");

    if (this->start == NULL && charArr[0] == '\0') 
        return result;

    else if (this->start != NULL && charArr[0] == '\0') {
        result.assign(*this);
        return result;
    }

    else if (this->start == NULL && charArr[0] != '\0') {
        result.assign(charArr);
        return result;
    }

    result.assign(*this);
    result.append(charArr);

    return result;
}

Helpers :: CharList Helpers :: CharList :: operator+ (const int num) {
    Helpers :: CharList result;    
    if (this->start != nullptr)
        result.append(*this);
    else
        result.forceInit();
    
    //std :: cout << ":: " << result.length() << ":" << this->length() << std :: endl;

    if (num > 0) {
        int n = num;
        CharNode *ptr = nullptr, *end=nullptr;
        int count = 0;
        while (n > 0) {
            CharNode *temp = new CharNode();
            !count && (end = temp);
            temp->ch = (n % 10) + '0';
            temp->next = ptr;
            ptr = temp;
            count++;
            n /= 10;
        }
        
        result.len += count;
        result.end->next = ptr;
        result.end = end;   
    }

    else {
        CharNode temp;
        temp.ch = '0';
        temp.next = nullptr;
        result.append(temp);
    }

    return result;
}