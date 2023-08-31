#include <iostream>
#include "../../includes/Web/Backgrounds.h"

// bool foo (Helpers::CharList &obj) {
//     obj.assign("hello");
//     return true;
// }

int main () {

    //char s[4] = "www";
    Helpers :: CharList cl1("hello");
    Helpers :: CharList cl2;
    Helpers :: CharList cl3(cl1);
    
    cl2 = cl1 + 102;

    std :: cout << "cl1 : " << cl1 << " >> " << cl1.length() << std :: endl;
    std :: cout << "cl2 : " << cl2 << " >> " << cl2.length() << std :: endl;
    std :: cout << "cl3 : " << cl3 << " >> " << cl3.length() << std :: endl;
    
    return 0;
}