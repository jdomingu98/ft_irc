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
 * Joins the vector of strings.
 * 
 * @param msg The vector of strings to be joined.
 * @param initialMsgPosition The position where the message begins
 * @param appendColon If `true`, the colon will be appended to the joined string. Default is `false`.
 * 
 * @return The joined string.
 */
const std::string join(const std::vector<std::string> &msg, size_t initialMsgPosition) {
    // TODO: Check if we need to call join at every command. In case we don't, we can remove the default value of appendColon.
    // and suppose that the colon will be appended to the joined string always.
    if (msg.empty() || initialMsgPosition >= msg.size())
        return NONE;
    
    std::vector<std::string> msgTokens(msg.begin() + initialMsgPosition, msg.end());
    std::string strJoined;

    if (msgTokens.empty())
        return NONE;

    strJoined = msgTokens[0];
    if (strJoined.size() > 0 && strJoined[0] == ':') {
        for (size_t i = 1; i < msgTokens.size(); i++)
            strJoined += " " + msgTokens[i];
        strJoined = strJoined.substr(1);
    }

    Logger::debug(strJoined); 
    return strJoined.empty() ? " " : strJoined;
}
