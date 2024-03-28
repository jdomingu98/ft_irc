#include "libsUtils.hpp"

/**
 * Trims the string. Removes the leading and trailing whitespaces.
 * 
 * @param str The string to be trimmed.
 * 
 * @return The trimmed string.
 */
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

/**
 * Splits the string by the delimiter.
 * 
 * @param s The string to be split.
 * @param delim The delimiter.
 * 
 * @return The vector of strings.
 */
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
