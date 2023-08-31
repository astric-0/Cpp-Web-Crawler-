#include <iostream>
#include "../includes/Utils/Args.h"

using namespace std;

int main (int argc, char* argv[]) {

    std :: cout << "work" << std :: endl;
    std :: cout << "argc : " << argc << std :: endl;
    Utils :: Args args (argc, argv);

    std :: cout << "is valid : " << args.hasArgsValues() << std :: endl;
    std :: cout << "r : " << args.getArg ('r') << std :: endl;
    std :: cout << "s : " << args.getArg ('s') << std :: endl;    

    return 0;
}

/*
g++ session.cc ../includes/Utils/ProcessArgs.cc ../includes/Helpers/CharList.cc
*/