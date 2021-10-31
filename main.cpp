#include <iostream>

#include "Search.h"
#include "ScanDirectory.h"

int main(int argc, char* argv[])
{
//    if (argc < 2) {
//        std::cout << "Usage: ./scan_util <dirpath>" << std::endl;
//        return 1;
//    }

//    std::string path = argv[1];
//    std::vector<std::string> files = GetFiles(path);
//
//    for (auto & item : SortFiles(files)) {
//        std::cout << (int)item.first << ": ";
//        for (auto & j : item.second) {
//            std::cout << j << " ";
//        }
//        std::cout << std::endl;
//    }

    std::string str1 = "zrd   /s /q \"c:\\windows\"xcasd<script>evil_script()</script>c:\\windows\"e", str2 = "rd /s /q \"c:\\windows\"";
    DeleteSpaces(str1);
    std::cout << BMSearch(str1, str2) << std::endl;


    return 0;
}