#include "libsUtils.hpp"

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
    while (std::getline(ss, item, delim))
        if (!item.empty())
            elems.push_back(item);
    return elems;
}

/**
 * Checks if the string is a number.
 * 
 * @param s The string to be checked.
 * 
 * @return `true` if the string is a number, `false` otherwise.
 */
bool isNumber(const std::string& s) {
    std::string::const_iterator it = s.begin();
    
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

/**
 * Gets the current date.
 * 
 * @return The string with the current date.
 */
std::string getCurrentDate() {
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    char buffer[100];

    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S UTC", now);
    return std::string(buffer);
}