#include <iostream>

#include "include/ScanDirectory.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: ./scan_util <dir_path>" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    FinalStat stat;
    stat.ScanDirectory(path);
    stat.PrintStat();

    return 0;
}