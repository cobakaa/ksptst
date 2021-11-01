#include "../include/Search.h"
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <vector>

bool StringsEquals(const std::string& str1, const std::string& str2) // case insensitive
{
    return std::equal(str1.begin(), str1.end(),
                      str2.begin(), str2.end(),
                      [](char s1, char s2) {
                          return tolower(s1) == tolower(s2);
                      });
}

std::vector<int> PrefixFunc(const std::string &str) {
    std::vector<int> prefs(str.length());

    int k = 0;
    prefs[0] = 0;
    for (int i = 1; i < str.length(); ++i) {
        while (k > 0 && str[k] != str[i]) {
            k = prefs[k - 1];
        }
        if (str[k] == str[i]) {
            ++k;
        }
        prefs[i] = k;
    }
    return prefs;
}

bool BMSearch(std::string &str, std::string &tmp) { // Boyer–Moore string-search algorithm
    if (str.length() < tmp.length()) {
        return false;
    }

    if (!tmp.length()) {
        return true;
    }

    std::unordered_map<char, int> stop_table;
    std::unordered_map<int, int> suffics_table;

    for (int i = 0; i < tmp.length(); ++i) {
        stop_table[tmp[i]] = i;
    }

    std::string rev_tmp(tmp.rbegin(), tmp.rend());
    std::vector<int> pref = PrefixFunc(tmp), pref_rev = PrefixFunc(rev_tmp);
    for (int i = 0; i < tmp.length() + 1; ++i) {
        suffics_table[i] = tmp.length() - pref.back();
    }

    for (int i = 1; i < tmp.length(); ++i) {
        int j = pref_rev[i];
        suffics_table[j] = std::min(suffics_table[j], i - pref_rev[i] + 1);
    }

    for (int shift = 0; shift <= str.length() - tmp.length();) {
        int pos = tmp.length() - 1;

        while (tmp[pos] == str[pos + shift]) {
            if (pos == 0) return true;
            --pos;
        }

        if (pos == tmp.length() - 1) {
            auto stop_symbol = stop_table.find(str[pos + shift]);
            int stop_symbol_additional = pos - (stop_symbol != stop_table.end() ? stop_symbol->second : -1);
            shift += stop_symbol_additional;
        } else {
            shift += suffics_table[tmp.length() - pos - 1];
        }
    }

    return false;
}

void DeleteSpaces(std::string& str) {
    for(int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') {
            i++;
            while (str[i] == ' ') {
                str.erase(i, 1);
            }
        }
    }
}
