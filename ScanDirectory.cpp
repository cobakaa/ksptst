#include "ScanDirectory.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

FinalStat ScanDirectory(const std::string& dir) {
    FinalStat fs;

    try {
        std::filesystem::path dir_path{dir};
        for (const auto & entry : std::filesystem::directory_iterator{dir_path}) {
            //

        }
    } catch (std::filesystem::filesystem_error const & ex) {
        std::cout
                << "code().message():  " << ex.code().message() << '\n';
    }

    return fs;
}


bool StringInFile(const std::string& path, std::string str) {

    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        throw std::filesystem::filesystem_error;
    }
    std::string file_content((std::istreambuf_iterator<char>(input_file)),
                             std::istreambuf_iterator<char>());

    DeleteSpaces(file_content);
    return BMSearch(file_content, str);
}

SuspicionType isSuitableFile(const std::string& path) {
    std::string ext = std::filesystem::path(path).extension();
    //погонять по паттерну
}