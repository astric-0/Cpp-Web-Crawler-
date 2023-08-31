#include <sys/stat.h>
#include "../Helpers/CharList.h"


namespace Utils {

    class Dir {
        public:
            static int makeDirRecusive (Helpers :: CharList, Helpers :: CharList [], int size);
            static int makeDirRecusive (const char* [], int size);
            static int makeDir (Helpers :: CharList &);
            static bool isDir (Helpers :: CharList &);
            static bool isDir (const char *);
    };
};