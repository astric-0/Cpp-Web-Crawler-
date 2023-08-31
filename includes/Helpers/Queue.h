#pragma once
#include "CharList.h"
#include <iostream>

namespace Helpers {

    class QueueNode {
        public:
            Helpers :: CharList str;
            QueueNode* next;            
            void add (const Helpers :: CharList &);        
    };

    class Queue {
        protected:
            QueueNode *start;
            QueueNode *end;
            unsigned int len;
            void init ();

        public:            
            Queue ();
            Queue (Queue &);
            ~Queue ();            

            void deleteQueue ();
            void enQ (Helpers :: CharList &);
            Helpers :: CharList deQ ();
            void extendShallowQ (Helpers :: Queue &);
            void extendQ (Helpers :: Queue &);
            unsigned int length ();

            void operator=(Helpers :: Queue &);

            friend std :: ostream& operator<< (std :: ostream &, const Queue &);
    };
};