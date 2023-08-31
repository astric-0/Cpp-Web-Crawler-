#pragma once
#include "../Helpers/Queue.h"
#include "../Utils/Args.h"
#include "Session.h"

namespace Web {

    class Crawler {
        private:
            Session *sessions[5];
            int sessionCount;

            Crawler() {                
                this->sessionCount = 0;              
            };

        protected:            
            bool sendRequest (Helpers :: CharList &, Helpers :: CharList &);

        public:
            static Crawler& getInstance () {
                static Crawler instance;
                return instance;
            }
            
            void execute (int);
            int createSession ();
            int createSession (int, char* []);
            bool deleteSession (int);

            Crawler& operator= (const Crawler &) = delete;
            Crawler (const Crawler &) = delete;
    };
};