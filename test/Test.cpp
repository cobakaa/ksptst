#include <iostream>
#include <filesystem>
#include <fstream>
#include <cassert>
#include "../include/ScanDirectory.h"

const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890";


int js_subs = 500;
int js_detects = 312;
int cmd_subs = 250;
int cmd_detects = 50;
int exe_subs = 100;
int exe_detects = 18;
int casual_files = 200;
int file_size = 1536;


std::string RandomFilename(int len, const std::string& ext = "") {
    std::string filename = "";
    for (int i = 0; i < len; ++i) {
        filename += alphabet[rand() % alphabet.length()];
    }
    filename += ext;
    return filename;
}

std::string RandomString(size_t size, const std::string& include = "") {
    std::string res = "";
    std::string new_alph = alphabet + "\n";

    int rand_pos = rand() % size;
    for (int i = 0; i < size; ++i) {
        res += (i == rand_pos) ? include : std::to_string(new_alph[rand() % new_alph.length()]);
    }
    return res;
}

void RandomFileGen(const std::string& name, size_t size, const std::string& include = "") {
    std::ofstream out(name, std::ios::out);
    out << RandomString(size, include);
    out.close();
}

void GenSusps(const std::filesystem::path& dir, SuspicionType type, int subs, int detects) {
    for (int i = 0; i < subs; ++i) {
        std::vector<std::string> possible_ext = PATTERN.at(type).first;
        std::string ext = possible_ext[rand() % possible_ext.size()];
        if (i < detects) {
            std::vector<std::string> possible_susps = PATTERN.at(type).second;
            RandomFileGen(dir.string() + "/" + RandomFilename(10, ext), file_size,
                          possible_susps[rand() % possible_susps.size()]);
        } else {
            RandomFileGen(dir.string() + "/" + RandomFilename(10, ext), file_size);
        }
    }
}

class Test {
public:
    void StartTest(const std::filesystem::path& path) {
        ClearDir(path);
        GenerateFiles(path);
        CheckResult(path);
    }

private:
    void ClearDir(const std::filesystem::path& dir) {
        std::filesystem::remove_all(dir);
    }

    void GenerateFiles(const std::filesystem::path& dir) {
        if (!std::filesystem::exists(dir)) {
            std::filesystem::create_directory(dir);
        }

        GenSusps(dir, SuspicionType::JS, js_subs, js_detects);
        GenSusps(dir, SuspicionType::CMD, cmd_subs, cmd_detects);
        GenSusps(dir, SuspicionType::EXE, exe_subs, exe_detects);
        for (int i = 0; i < casual_files; ++i) {
            if (i < 50) {
                std::vector<SuspicionType> pos_type = {SuspicionType::JS, SuspicionType::CMD, SuspicionType::EXE}; // files with strings
                std::vector<std::string> pos_pattern = PATTERN.at(pos_type[rand() % pos_type.size()]).second;
                std::string rand_pattern = pos_pattern[rand() % pos_pattern.size()];
                RandomFileGen(dir.string() + "/" + RandomFilename(10, ".json"), 1024, rand_pattern);
            } else {
                RandomFileGen(dir.string() + "/" + RandomFilename(10, ".json"), 1024);
            }
        }
    }

    void CheckResult(const std::filesystem::path& dir) {
        FinalStat fs;
        fs.ScanDirectory(dir);
        assert(fs.processed_files_num == js_subs + exe_subs + cmd_subs + casual_files);
        std::cout << "Processed files number... PASSED" << std::endl;
        assert(fs.js_detects_num == js_detects);
        std::cout << "JS files number... PASSED" << std::endl;
        assert(fs.cmd_detects_num == cmd_detects);
        std::cout << "CMD files number... PASSED" << std::endl;
        assert(fs.exe_detects_num == exe_detects);
        std::cout << "EXE files number... PASSED" << std::endl;
    }
};

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Usage ./test <dir_path>";
        return 1;
    }

    std::string path = argv[1];
    Test test;
    test.StartTest(std::filesystem::path(path));


    return 0;
}