#include <ios>
#include <iostream>
#include <fstream>
#include "../../includes/Web/Session.h"
#include "../../includes/Helpers/CharList.h"
#include "../../includes/Helpers/Queue.h"

void write () {
    Web :: Data dStruct;

    dStruct.count = 0;
    dStruct.currLevel = 0;
    dStruct.name = "ASTRIC";
    dStruct.seedUrl = "WWW.GOOGLE.COM";

    std :: ofstream file_obj;
    file_obj.open("abc.txt", std :: ios :: app);
    file_obj.write((char*)&dStruct, sizeof(dStruct));
}

void read () {
    Web :: Data dStruct;    
    std :: ifstream file_obj;
    file_obj.open("abc.txt", std :: ios :: in);
    file_obj.read((char*)&dStruct, sizeof(dStruct));

    std :: cout << dStruct.count << std :: endl;
    std :: cout << dStruct.currLevel << std :: endl;
    std :: cout << dStruct.name << std :: endl;
    std :: cout << dStruct.seedUrl << std :: endl;
}

void writeQ () {
    Web :: Data dStruct;
    dStruct.name = "astric";

    // Helpers::CharList x[5];

    // x[0] = "www.google0.com";
    // x[1] = "www.google1.com";
    // x[2] = "www.google2.com";
    // x[3] = "www.google3.com";
    // x[4] = "www.google4.com";

    // int i = 0;
    // while (i < 5)
    //     dStruct.currQueue.enQ(x[i++]);
    
    std :: ofstream file_obj;
    file_obj.open("currQueue.txt", std :: ios :: trunc);
    file_obj << dStruct.currQueue;
    file_obj.close();
}

void readQ () {
    char ch;

    std :: ifstream file_obj;
    file_obj.open("currQueue.txt", std :: ios :: in);
    
    Helpers :: CharList singleUrl;
    Helpers :: Queue que;

    while (file_obj >> ch) {
        if (ch == '\n') {
            que.enQ(singleUrl);
            singleUrl.deleteCharList();
            continue;
        }
        singleUrl.append(ch);
    }
    
    std :: cout << "WORKED ?? " << std :: endl;
    std :: cout << que << std :: endl;
    std :: cout << que.length() << std :: endl;
}

int main () {    
    //writeQ();
    readQ();
    return 0;
}