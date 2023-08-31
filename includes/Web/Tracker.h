#pragma once
#include <iostream>

namespace Web {
    class Tracker {
        private:
            long *data;
            long capacity;
            long size;

            void stats (long, int);

        public:
            Tracker ();
            ~Tracker ();
            Tracker (Tracker &);

            long push (const long);
            bool search (const long, int &);
            long search (const long);            
            void print ();
            long getSize ();
            long getCapacity ();
            void deleteTracker ();

            long operator [] (const long);
            Tracker operator = (const Tracker &);
            friend std :: ostream& operator << (std :: ostream &, const Tracker &);
            //Tracker (const Tracker &) = delete;
            //void operator = (const int) = delete;                        

    };    
};