#include "../../includes/Web/Crawler.h"

int main (int argc, char* argv[]) {

    Web :: Crawler &crawler = Web :: Crawler :: getInstance();
    int index = crawler.createSession(argc, argv);
    crawler.execute(index);

    return 0;
}