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
 * @param msg The vector of strings.
 * 
 * @return The joined string.
 */
std::string join(const std::vector<std::string> &msg) {
    std::vector<std::string>::const_iterator it = msg.begin();

    while (it != msg.end() && it->find(":") == std::string::npos) {
        ++it;
    }

    if (it == msg.end()) {
        return "";
    }
    if (it + 1 == msg.end()){
        std::string word = it->substr(it->find(":"));
        for (int i = 0; word[i] != '\0'; i++){
            word[i] = word[i + 1];
        }
        std::cout << "word: " << word << std::endl;
        return word;
    }

    std::string joined = it->substr(it->find(":") + 1);
    for (++it; it != msg.end(); ++it) {
        joined += " " + *it;
    }
    return joined;
}