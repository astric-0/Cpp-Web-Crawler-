#pragma once

#include <libxml/HTMLparser.h>
#include "../Helpers/Queue.h"
#include "Tracker.h"

namespace Web {
    class Backgrounds {
        private: 
            Backgrounds () {};

        protected:
            static Helpers :: Queue newURLs;
            static Helpers :: CharList hostUrl;
            static Tracker tracker;         

        public:
            static void init (Helpers :: CharList &, Tracker &);
            static void reset ();

            static Tracker getTracker ();

            static void nodeTraverser (xmlNode *node);        
            static bool filterURLs (Helpers :: CharList &);
            static void fillNewURLs (Helpers :: Queue &);
            static int newURLsLength ();            
    };    
};