
#ifndef KSPTST_SCANDIRECTORY_H
#define KSPTST_SCANDIRECTORY_H

#include <vector>
#include <filesystem>
#include <string>
#include <unordered_map>
#include "Search.h"

enum struct SuspicionType {
    JS,
    CMD,
    EXE,
    NONE
};

struct FinalStat {
    int processed_files_num = 0;
    int js_detects_num = 0;
    int cmd_detects_num = 0;
    int exe_detects_num = 0;
    int errors_num = 0;

};

const std::unordered_map<SuspicionType, std::pair<std::vector<std::string>, std::vector<std::string>>> PATTERN = {
        {SuspicionType::JS, {{".js"}, {"<script>evil_script()</script>"}}},
        {SuspicionType::CMD, {{".cmd", ".bat"}, {R"(rd /s /q "c:\windows")"}}},
        {SuspicionType::EXE, {{".exe", ".dll"}, {"CreateRemoteThread", "CreateProcess"}}}
};

std::vector<std::string> GetFiles(const std::string& path);


bool StringInFile(const std::string& path, std::string str);
FinalStat ScanDirectory(const std::string& dir);
SuspicionType GetSuspicionType(const std::string& path);


#endif //KSPTST_SCANDIRECTORY_H
