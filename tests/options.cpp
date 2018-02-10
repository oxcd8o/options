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

    oxcd8o::Options op;
    auto config = op.argument("-c", "--config").mandatory().help("Path to configuration file.");
    auto log = op.argument("-l", "--log").help("Path to log file.");
    auto flag = op.argument("-f", "--flag").valueless().help("Some unknown flag.");

    std::cout << op;

    op.parse(argc, argv);

    return 0;
}