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
    while (it != str.end() && std::isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = str.rbegin();
    while (rit.base() != it && std::isspace(*rit))
        rit++;

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
    while (std::getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

/**
 * Joins the vector of strings.
 * 
 * @param msg The vector of strings to be joined.
 * @param initialMsgPosition The position where the message begins
 * 
 * @return The joined string.
 */
const std::string join(const std::vector<std::string> &msg, size_t initialMsgPosition) {
    std::string strJoined;

    for (size_t i = initialMsgPosition; i < msg.size(); i++) {
        Logger::debug(msg[i]);
    }

    if (msg.empty())
        return NONE;
    
    std::vector<std::string> msgTokens(msg.begin() + initialMsgPosition, msg.end());
    for (size_t i = 0; i < msgTokens.size(); i++) {
        Logger::debug(msgTokens[i]);
    }
    strJoined += msgTokens[0];    

    for (size_t i = 1; i < msgTokens.size(); i++)
        strJoined += " " + msgTokens[i];

    Logger::debug(strJoined); 
    return strJoined;
}


/**
 * Checks if the string contains a colon.
 * 
 * @param msg The vector of strings.
 * 
 * @return `true` if the vector only have spaces, `false` otherwise.
 */
bool isColonPresent(const std::vector<std::string> &msg) {
    std::vector<std::string>::const_iterator it = msg.begin();
    
    while (it != msg.end() && it->find(":") == std::string::npos)
        it++;
    return it != msg.end();
}

/**
 * Checks if the vector only have spaces.
 * 
 * @param msg The vector of strings.
 * 
 * @return `true` if the vector only have spaces, `false` otherwise.
 */
bool haveOnlySpaces(const std::vector<std::string> &msg) {
    std::vector<std::string> msgToken(msg.begin() + 2, msg.end());
    
    for (std::vector<std::string>::const_iterator it = msgToken.begin(); it != msgToken.end(); it++) {
        for (size_t i = 0; i < it->size(); i++) {
            if (!std::isspace((*it)[i]))
                return false;
        }
    }
    return true;
}