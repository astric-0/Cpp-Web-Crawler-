#include <fstream>
#include <iostream>
#include "../../includes/Web/Tracker.h"

void print (Web :: Tracker &t1) {    
    std :: cout << "TEST PRINTING";
    int len = t1.getSize();
    for (int i = 0; i < len; i++)
        std :: cout << t1[i] << ' ';
    std :: cout << std :: endl;
}

Web :: Tracker makeTracker () {
    Web :: Tracker t1;

    t1.push(1);
    t1.push(4);
    t1.push(7);
    t1.push(2);
    t1.push(4);
    t1.push(1);
    t1.push(5);
    t1.push(0);
    t1.push(8);
    t1.push(3);
    t1.push(2);
    t1.push(3);
    t1.push(6);

    //print(t1);
    return t1;
}

void checkPointer (Web :: Tracker &t1) {
    Web :: Tracker tObj = t1;
    std :: cout << "PRINTING USING POINTER : ";
    tObj.push(1000000);
    tObj.print();        
    //&tObj = nullptr;
    std :: cout << std :: endl;
}

void vReader () {
    Web :: Tracker t1;
    std :: ifstream fObj;
    fObj.open("../testNewCrawler/TEST_VISITED_CODES/visited.txt", std :: ios :: in);    
    long num;
    while (fObj >> num)
        t1.push(num);
    
    fObj.close();
}

int main () {  
    vReader();
    return 0;
}