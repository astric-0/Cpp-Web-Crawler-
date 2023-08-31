#include <iostream>
#include <stdexcept>
#include "includes/CharList.h"

int main() {
    Helpers :: CharList* c1;

    c1 = new Helpers :: CharList[10];

    c1[0] = "hello";
    c1[1] = "yellow";

    for (int i = 0; i < 2; i++)
        std :: cout << c1[i] << std :: endl;

    delete [] c1;    

    c1 = new Helpers :: CharList[2];
    c1[0] = "person 1";
    c1[1] = "person 2";

    for (int i = 0; i < 2; i++)
        std :: cout << c1[i] << std :: endl;    
}

// g++ -o ./a_out test.cc -lPocoNet -lPocoFoundation