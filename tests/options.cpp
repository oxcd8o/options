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

    auto op = oxcd8o::Options().allowUnknown();
    auto config = op.argument("-c", "--config").mandatory().help("Path to configuration file.").metavar("<path>");
    auto log = op.argument("-l", "--log").help("Path to log file.").defaultValue("/path/to/log");
    auto flag = op.argument("-f", "--flag").valueless().help("Some unknown flag.");

    std::cout << op.getHelp();

    op.parse(argc, argv);

    std::cout << "Config: " << config.as<std::string>() << std::endl;
    std::cout << "Log: " << log.as<std::string>() << std::endl;
    std::cout << "Flag: " << flag.as<bool>() << std::endl;

    return 0;
}