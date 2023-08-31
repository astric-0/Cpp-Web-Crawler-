#pragma once
#include <iostream>

namespace Helpers {
    class CharNode {
        public:
            char ch;
            CharNode *next;
    };

    class CharList {
        protected:
            CharNode *start;
            CharNode *end;
            int len;
            unsigned long id;
            bool isShallowCopy;
            void init ();
            void forceInit ();
            void setId ();

        public:
            CharList ();
            CharList (const char *);
            CharList (const CharList &);            
            ~CharList ();

            void assign (const char *);
            void assign (const CharList &);            
            void append (const char *, int size = -1);
            void append (const CharList &);
            void append (const CharNode &);
            void append (const char &);

            int find (const CharList &);
            int find (const char);
            unsigned long getId ();

            void print ();
            void makeShallowCopy (const CharList &);

            int length ();

            bool deleteCharList ();
            bool fill (char *, int);            
            bool isShallow ();

            CharList operator= (const CharList &);
            CharList operator= (const char *);
            CharList operator+ (const CharList &);
            CharList operator+ (const char *);
            CharList operator+ (const int);
            void operator+= (const CharList &);                   
            // void operator== (const CharList &);
            // void operator== (const char *);
            
            friend std :: ostream& operator<< (std :: ostream &, CharList );     
    };

};