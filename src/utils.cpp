#include "utils.hpp"

std::string trim(const std::string& str) {
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isspace(*it)) {
        it++;
    }

    std::string::const_reverse_iterator rit = str.rbegin();
    while (rit.base() != it && std::isspace(*rit)) {
        rit++;
    }

    return std::string(it, rit.base());
}
