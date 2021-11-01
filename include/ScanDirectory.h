
#ifndef KSPTST_SCANDIRECTORY_H
#define KSPTST_SCANDIRECTORY_H

#include <vector>
#include <filesystem>
#include <string>
#include <unordered_map>
#include "Search.h"
#include "Timer.h"

enum struct SuspicionType {
    JS,
    CMD,
    EXE,
    NONE,
    ERROR
};

class FinalStat {
public:
    void PrintStat();
    void ScanDirectory(const std::string& dir);


private:
    int processed_files_num = 0;
    int js_detects_num = 0;
    int cmd_detects_num = 0;
    int exe_detects_num = 0;
    int errors_num = 0;

    void ChangeStat(const SuspicionType& t);

    Timer timer;
};

const std::unordered_map<SuspicionType, std::pair<std::vector<std::string>, std::vector<std::string>>> PATTERN = {
        {SuspicionType::JS, {{".js"}, {"<script>evil_script()</script>"}}},
        {SuspicionType::CMD, {{".cmd", ".bat"}, {R"(rd /s /q "c:\windows")"}}},
        {SuspicionType::EXE, {{".exe", ".dll"}, {"CreateRemoteThread", "CreateProcess"}}}
};

bool StringInFile(const std::string& path, std::string str);

SuspicionType GetSuspicionType(const std::string& path);


#endif //KSPTST_SCANDIRECTORY_H
