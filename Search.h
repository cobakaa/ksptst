
#ifndef KSPTST_SEARCH_H
#define KSPTST_SEARCH_H

#include <string>
#include <filesystem>

bool StringsEquals(const std::string& str1, const std::string& str2);
bool BMSearch(std::string &str, std::string &tmp);
void DeleteSpaces(std::string& str);
#endif //KSPTST_SEARCH_H
