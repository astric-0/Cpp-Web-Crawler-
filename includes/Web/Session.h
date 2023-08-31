#pragma once

#include "../Helpers/CharList.h"
#include "../Helpers/Queue.h"
#include "../Utils/Args.h"
#include "Tracker.h"

namespace Web {

    const Helpers :: CharList DEFAULT_URL ("https://github.com");
    const Helpers :: CharList LEVEL_FILE_NAME ("/currLevel.txt");
    const Helpers :: CharList COUNT_FILE_NAME ("/currCount.txt");
    const Helpers :: CharList CURR_QUEUE_FILE_NAME ("/currQueue.txt");
    const Helpers :: CharList NEXT_QUEUE_FILE_NAME ("/nextQueue.txt");
    const Helpers :: CharList SESSION_FILENAME ("/sessionName.txt");
    const Helpers :: CharList VISITED_FILENAME ("/visited.txt");

    struct Data {
        Helpers :: CharList name;
        Helpers :: CharList seedUrl;
        Helpers :: Queue currQueue;
        Helpers :: Queue nextQueue;        

        int count;
        int currLevel;
    };

    class Session {
        private:
            Data sessionData;
            static void qReader (Helpers :: CharList &, Helpers :: Queue &);
            static int iReader (Helpers :: CharList &);
            static void vReader (const Helpers :: CharList &, Tracker &);

        public:
            Tracker visited;
            Session ();
            Session (int, char* []);

            void resume ();
            void print ();
            void saveQueues ();
            void saveFileName ();
            void saveCurrLevel ();
            void saveCurrCount ();
            void saveVisited ();

            //void setTracker (Tracker);
            //Tracker getTracker ();

            int currQueueLength ();
            int nextQueueLength ();
            Helpers :: CharList deCurrQ ();
            void extendNextQ (Helpers :: Queue &);
            void increaseCount ();
            void levelUp ();

            Helpers :: CharList getName ();
            int getCount ();
            int getLevel ();
    };    
};