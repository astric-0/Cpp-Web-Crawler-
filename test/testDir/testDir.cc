#include "../../includes/Utils/Dir.h"
#include "../../includes/Utils/DateString.h"
#include <iostream>
#include<unistd.h>

int main () {
    // Helpers :: CharList filename (Utils :: DateString :: getCurrentDateTimeString());
    // int check = Utils :: Dir :: makeDir(filename);
    // std :: cout << check << std :: endl;

    // Helpers :: CharList filename ("testingdir");

    // Helpers :: CharList dirs[3], preset("./");
    // dirs[0] = filename;
    // dirs[1] = "hello";
    // dirs[2] = "bye";

    // int check = Utils :: Dir :: makeDirRecusive(preset, dirs, 3);    
    // std :: cout << check << std :: endl;

    //Helpers :: CharList path ("test1/test2");
    //char path[] = "test1/test2";
    //std :: cout << Utils :: Dir :: isDir(path) << std :: endl;

  
    std :: cout << Utils :: DateString :: getCurrMilliSeconds() << std :: endl;    
    unsigned int microsecond = 1000000;
    usleep(3 * microsecond);
    std :: cout << Utils :: DateString :: getCurrMilliSeconds() << std :: endl;     
    return 0;
}