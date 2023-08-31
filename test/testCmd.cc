#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

using namespace std;

string exec(string command) {
    char buffer[128];
    string result = "";

    // Open pipe to file
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "popen failed!";
    }

    // read till end of process:
    while (!feof(pipe)) {

        // use buffer to read and add to result
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }

    pclose(pipe);
    return result;
}

void execTest () {
    string cmd = exec("curl https://github.com");
    cout << cmd << cmd.length();
    cout << endl;
}

int main() {
    system("(curl https://www.google.com >> delete.html) > /dev/null 2>&1");
    return 0;
}