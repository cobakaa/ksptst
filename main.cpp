#include <iostream>

#include "include/ScanDirectory.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: ./ksptst <dir_path>" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    FinalStat stat;
    stat.ScanDirectory(std::filesystem::path(path));
    std::cout << stat << std::endl;

    return 0;
}