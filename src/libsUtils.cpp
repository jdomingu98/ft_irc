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

/**
 * Joins the vector of strings.
 * 
 * @param msg The vector of strings to be joined.
 * 
 * @return The joined string.
 */
const std::string join(const std::vector<std::string> &msg) {
  std::vector<std::string>::const_iterator it = msg.begin();

    while (it != msg.end() && it->find(":") == std::string::npos)
        ++it;
    if (it == msg.end())
        return NONE;
    std::string joined;
    if (*it != ":")
        joined = it->substr(1);
    else if (it + 1 == msg.end())
        return NONE;
    ++it;
    for (; it != msg.end(); ++it)
        joined += " " + *it;
    return joined;
}


/**
 * Checks if the string contains a colon.
 * 
 * @param msg The vector of strings.
 * 
 * @return `true` if the vector only have spaces, `false` otherwise.
 */
bool isColon(const std::vector<std::string> &msg) {
    std::vector<std::string>::const_iterator it = msg.begin();
    while (it != msg.end() && it->find(":") == std::string::npos)
        ++it;
    return it != msg.end();
}

/**
 * Checks if the vector only have spaces.
 * 
 * @param msg The vector of strings.
 * 
 * @return `true` if the vector only have spaces, `false` otherwise.
 */
bool isOnlySpaces(const std::vector<std::string> &msg) {
    std::vector<std::string> msgToken(msg.begin() + 2, msg.end());
    for (std::vector<std::string>::const_iterator it = msgToken.begin(); it != msgToken.end(); ++it) {
        for (size_t i = 0; i < it->size(); i++) {
            if ((*it)[i] != ' ')
                return false;
        }
    }
    return true;
}