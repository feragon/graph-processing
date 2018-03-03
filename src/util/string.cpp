#include "string.h"

bool compareCharInsensitive(unsigned char a, unsigned char b) {
    return std::tolower(a) == std::tolower(b);
}

bool compareCaseInsensitive(const std::string& s1, const std::string& s2) {
    if(s1.length() != s2.length()) {
        return false;
    }

    return std::equal(s1.begin(), s1.end(), s2.begin(), compareCharInsensitive);
}
