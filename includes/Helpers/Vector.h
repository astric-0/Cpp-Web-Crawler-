#pragma once
#include <iostream>

namespace Helpers {
    template <typename T> class Vector {
        private:
            long size;
            long capacity;
            T *data;
        public:
            Vector ();
            Vector (std :: size_t);

            void push (T);
            T pop ();
            void reserve (std :: size_t);
            long getSize ();
            long getCapacity ();

            T& operator [] (const long);
            //template <typename FT>
            //friend std :: ostream& operator << (std :: ostream &, Vector<FT> v);
    };
};

#include "Vector.cc"