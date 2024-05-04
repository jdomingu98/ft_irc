#include "Utils.hpp"

/**
 * The utils constructor.
 */
Utils::Utils() {}

/**
 * The utils destructor.
 */
Utils::~Utils() {}

/**
 * Splits the string by the delimiter.
 * 
 * @param s The string to be split.
 * @param delim The delimiter.
 * 
 * @return The vector of strings.
 */
std::vector<std::string> Utils::split(const std::string &s, const char delim) {
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
bool Utils::isNumber(const std::string& s) {
    if (s == "-")
        return false;
    std::string::const_iterator it = s.begin();
    
    while (it != s.end() && (std::isdigit(*it) || (*it == '-' && it == s.begin())))
        ++it;
    return !s.empty() && it == s.end();
}