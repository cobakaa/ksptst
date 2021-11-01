#include "../include/ScanDirectory.h"
#include <iostream>
#include <fstream>
#include <future>

void FinalStat::ScanDirectory(const std::filesystem::path& dir) {
    timer.Start();

    std::vector<std::future<SuspicionType>> fut_vec;

    for (const auto & entry : std::filesystem::directory_iterator{dir}) {
        if (is_regular_file(entry)) {

            fut_vec.push_back(std::async(std::launch::async, [](const std::filesystem::path& p) { // with parameter
                return GetSuspicionType(p);
            }, entry.path()));
//            ChangeStat(GetSuspicionType(entry.path()));
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

std::ostream& operator<< (std::ostream &out, const FinalStat &fs) {
    out << "====== Scan result ======" << "\n\n"
    << "Processed files: " << fs.processed_files_num << "\n\n"
    << "JS detects: " << fs.js_detects_num << "\n\n"
    << "CMD detects: " << fs.cmd_detects_num << "\n\n"
    << "EXE detects: " << fs.exe_detects_num << "\n\n"
    << "Errors: " << fs.errors_num << "\n\n"
    << "Execution time: " << fs.timer.hours.count() << ":" << fs.timer.mins.count()
    << ":" << fs.timer.secs.count() << " " << fs.timer.t.count() << "\n\n"
    << "=========================" << std::endl;

    return out;
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

SuspicionType GetSuspicionType(const std::filesystem::path& path) {
    std::string ext = path.extension().string();
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