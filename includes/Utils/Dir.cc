#include "Dir.h"
#include <sys/stat.h>

int Utils :: Dir :: makeDirRecusive (Helpers :: CharList preset, Helpers :: CharList dirs[], int size) {

    int i = 0;
    if(!preset.length()) preset = "./";
    Helpers :: CharList currDir(preset);

    while (i < size) {
        currDir += dirs[i] + "/";
        int charSize = currDir.length();
        char dirname[charSize];
        currDir.fill(dirname, charSize);

        if (isDir(dirname)) {
            i++;
            continue;
        }

        //std :: cout << dirname << std :: endl;

        int errorCheck = mkdir(dirname, 0777);
        if (errorCheck) return errorCheck;

        i++;
    }

    return 0;
}

int Utils :: Dir :: makeDirRecusive (const char* dirs[], int size) {

    int i = 0;
    char currDir[] = "./";
    while (i < size) {
        //currDir += dirs[i] + "/";
        //int charSize = currDir.length();

        //char dirname[charSize];
        //currDir.fill(dirname, charSize);

        //std :: cout << dirname << std :: endl;

        // int errorCheck = mkdir(dirname, 0777);
        // if (errorCheck) return errorCheck;

        i++;
    }

    return 0;
}

int Utils :: Dir :: makeDir (Helpers :: CharList &dirname) {
    int size = dirname.length();
    if (size == 0) return -1;
    char charDirname [size];
    dirname.fill(charDirname, size);
    return mkdir(charDirname, 0777);
}

bool Utils :: Dir :: isDir(Helpers::CharList &path) {
    int size = path.length();
    char charPath[size];
    path.fill(charPath, size);

    struct stat sb;
    return (stat(charPath, &sb) == 0);
}

bool Utils :: Dir :: isDir(const char *path) {    
    struct stat sb;
    return (stat(path, &sb) == 0);
}

/*
g++ testDir.cc ../../includes/Utils/Dir.cc ../../includes/Helpers/CharList.cc
*/