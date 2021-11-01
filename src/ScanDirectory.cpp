#include "../include/ScanDirectory.h"
#include <iostream>
#include <fstream>
#include <future>

void FinalStat::ScanDirectory(const std::string& dir) {
    timer.Start();

    std::vector<std::future<SuspicionType>> fut_vec;

    std::filesystem::path dir_path{dir};
    for (const auto & entry : std::filesystem::directory_iterator{dir_path}) {
        if (is_regular_file(entry)) {

            fut_vec.push_back(std::async(std::launch::async, [](const std::string& str) { // with parameter
                return GetSuspicionType(str);
            }, entry.path().string()));
        }
    }

    for (auto & f : fut_vec) {
        ChangeStat(f.get());
    }
    timer.Finish();
}

void FinalStat::ChangeStat(const SuspicionType& t) {
    processed_files_num++;
    switch (t) {
        case SuspicionType::JS:
            js_detects_num++;
            break;

        case SuspicionType::CMD:
            cmd_detects_num++;
            break;

        case SuspicionType::EXE:
            exe_detects_num++;
            break;

        case SuspicionType::ERROR:
            errors_num++;

        default:
            break;
    }
}

void FinalStat::PrintStat() {
    std::cout << "====== Scan result ======" << "\n\n"
    << "Processed files: " << processed_files_num << "\n\n"
    << "JS detects: " << js_detects_num << "\n\n"
    << "CMD detects: " << cmd_detects_num << "\n\n"
    << "EXE detects: " << exe_detects_num << "\n\n"
    << "Errors: " << errors_num << "\n\n";
    std::cout << "Execution time: " << timer.hours.count() << ":" << timer.mins.count() << ":"
    << timer.secs.count() << " " << timer.t.count() << "\n\n"
    << "=========================" << std::endl;
}

bool StringInFile(const std::string& path, std::string str) {

    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        throw std::exception();
    }
    std::string file_content((std::istreambuf_iterator<char>(input_file)),
                             std::istreambuf_iterator<char>());

    DeleteSpaces(file_content);
    return BMSearch(file_content, str);
}

SuspicionType GetSuspicionType(const std::string& path) {
    std::string ext = std::filesystem::path(path).extension().string();
    for (auto & item : PATTERN) {
        for (auto & p_ext : item.second.first) {
            if (StringsEquals(p_ext, ext)) {
                for (auto & p_str : item.second.second) {
                    try{
                        if (StringInFile(path, p_str)) {
                            return item.first;
                        }
                    } catch (...) {
                        return SuspicionType::ERROR;
                    }
                }
            }
        }
    }
    return SuspicionType::NONE;
}