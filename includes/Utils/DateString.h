#pragma once
#include "../Helpers/CharList.h"

namespace Utils {

    class DateString {
        public:
            static Helpers :: CharList getCurrentDateTimeString ();
            static Helpers :: CharList getCurrentDateTimeString (Helpers::CharList &, const Helpers::CharList &, const Helpers::CharList &);
            static unsigned long getCurrMilliSeconds ();
    };
};