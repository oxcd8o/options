#include "include/options.h"
#include "include/error.h"

#include <iostream>

int main(int argc, char** argv)
{
    try {
        throw oxcd8o::ValueError() << "blah" << " " << "blah" << " " << "blah" << 111;
    } catch (const oxcd8o::Error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    oxcd8o::Options op(argc, argv);

    return 0;
}