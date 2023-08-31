#include <iostream>
#include "../../includes/Web/Session.h"

int main (int argc, char* argv[]) {
    Web :: Session s(argc, argv);
    //Web :: Session s;
    s.print();
    return 0;
}