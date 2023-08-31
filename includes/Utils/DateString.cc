#include "DateString.h"
#include <ctime>

Helpers :: CharList Utils :: DateString :: getCurrentDateTimeString () {

    Helpers :: CharList datetime;
    Helpers :: CharList gap (":");
    Helpers :: CharList start ("");
    Helpers :: CharList end ("");
    Helpers :: CharList space ("_");

    auto t = std :: time(nullptr);
    auto tm = *std :: localtime(&t);

    datetime = start + tm.tm_mday + gap + tm.tm_mon + gap + (1900 + tm.tm_year) + space + tm.tm_hour + gap + tm.tm_min + gap + tm.tm_sec + end;

    return datetime;    
}

Helpers :: CharList Utils :: DateString :: getCurrentDateTimeString (Helpers :: CharList &start, const Helpers :: CharList &end, const Helpers :: CharList &gap) {

    Helpers :: CharList datetime;
    Helpers :: CharList space ("  ");

    auto t = std :: time(nullptr);
    auto tm = *std :: localtime(&t);

    datetime = start + tm.tm_mday + gap + tm.tm_mon + gap + (1900 + tm.tm_year) + space + tm.tm_hour + gap + tm.tm_min + gap + tm.tm_sec + end;

    return datetime;
}

unsigned long Utils :: DateString :: getCurrMilliSeconds () {
    auto t = std :: time(nullptr);    
    return t;
}