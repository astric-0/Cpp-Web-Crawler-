#pragma once

#include "../Helpers/CharList.h"

namespace Utils {
    class Args {
        private:
            bool isNull;            
            Helpers :: CharList restart;
            Helpers :: CharList session;

        public:
            Args ();
            Args (const int, char* []);
            
            Helpers :: CharList getArg (const char);
            void process (const int, char* []);
            bool hasArgsValues ();

            bool static isValidArg (const char &);

            //Args (const Args &) = delete;
            //Args operator = (const Args &) = delete;
    };
}