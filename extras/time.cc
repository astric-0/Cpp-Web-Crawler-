#include <iostream>
#include <ostream>
#include "../includes/Utils/DateString.h"

int main () {
    //while (true) {
    Helpers :: CharList datetime;
    datetime = Utils :: DateString :: getCurrentDateTimeString();
    std :: cout << datetime << std :: endl;   

    Helpers :: CharList start (""), end (""), gap (":");    
    datetime = Utils :: DateString :: getCurrentDateTimeString(start, end, gap);
    std :: cout << datetime << std :: endl;
    //}
}

/*
int main () {

    auto t = std :: time(nullptr);
    auto tm = *std :: localtime(&t);
    //std :: cout << t << std :: endl;
    std :: cout << 1900 + tm.tm_year << " : " << std :: endl;
    std :: cout << tm.tm_mday << " : " << tm.tm_mon << " : " << tm.tm_year << std :: endl;
    std :: cout << tm.tm_hour << " : " << tm.tm_min << " : " << tm.tm_sec << std :: endl;

    //char *timeString = tm.tm_mday + " : " + 
    //char *timeString[] = std :: put_time(&tm, "%d-%m-%Y %H-%M-%S");
    //std :: cout << std :: put_time(&tm, "%d-%m-%Y %H-%M-%S") << std::endl;
}
*/