#include "Args.h"

Utils :: Args :: Args () {
    this->isNull = true;
}

Utils :: Args :: Args (const int argc, char* argv[]) {
    this->process(argc, argv);
}

bool Utils :: Args :: isValidArg (const char &arg) {
    const char validArgs[] = "sSRr";

    bool check = false;
    int i = 0;
    do {
        if (arg == validArgs[i])
            return true;
        i++;
    } while (!check && validArgs[i] != '\0');

    return false;
}

void Utils :: Args :: process (const int argc, char* argv[]) {
    struct Args args;

    int i = 1;
    while (i < argc) {
        if (argv[i][0] != '-') {
            i++;
            continue;             
        }

        char switchExpression = argv[i][1];

        char* argValue = argv[i+1];
        if (argValue[0] == '\0') { 
            i++;
            continue;
        }

        if (this->isNull && Utils :: Args :: isValidArg (switchExpression)) 
            this->isNull = false;
        
        switch (switchExpression) {
            case 'R' :
            case 'r' : this->restart = argValue;
                    break;

            case 'S' :
            case 's' : this->session = argValue;
                    break;
        };
        i+=2;
    }    
}

Helpers :: CharList Utils :: Args :: getArg (const char arg) {
    Helpers :: CharList argValue;
    switch (arg) {
        case 'R' :
        case 'r' :  argValue = this->restart;
                    break;

        case 'S' :
        case 's' :  argValue = this->session;            
                    break;
    };

    return argValue;
}

bool Utils :: Args :: hasArgsValues () {
    return ! this->isNull;
}