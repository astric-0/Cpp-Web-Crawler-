#include "../../includes/Helpers/Queue.h"
#include <iostream> 

int main () {
    Helpers :: CharList c1, c2, c3;

    c1 = "OMEN";
    c2 = "THE PERKS OF BEING A WALLFLOWER";
    c3 = "DEAD POETS SOCIETY";

    Helpers :: Queue q1;
    Helpers :: Queue q2;
    Helpers :: Queue q3;

    q1.enQ(c1);    

    std :: cout << q1 << std :: endl;
    std :: cout << q1.deQ();
    //q1.enQ(c2);
    //q1.enQ(c3);

    q2.enQ(c1);
    q2.enQ(c3);
    q2.deQ();

    //q1.extendQ(q2);

    std :: cout << q1 << std :: endl << q1.length() << std :: endl;
    std :: cout << q2 << std :: endl << q2.length() << std :: endl;    
    return 0;
}