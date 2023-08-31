#pragma once
#include "../Helpers/CharList.h"

namespace Web {
    class Url : public Helpers :: CharList {
        public:
            Url ();
            Url (const char *);
            Url (const Helpers :: CharList &);

            bool getDomain (Helpers :: CharList &);            
    };
};