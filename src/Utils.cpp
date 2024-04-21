#include "Utils.hpp"

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
 * Returns the RPL_NAMES_REPLY message.
 * 
 * @param channelName The name of the channel
 * @param opers The vector of operators in the channel
 * @param users The vector of users in the channel
 * 
 * @return The RPL_NAMES_REPLY message
 */
const std::string &rplNamesReply(const std::string &nickname, const Channel &channel) {
    std::string channelName = channel.getName();
    std::string msg = channelName + " :";

    std::vector<User> users = channel.getUsers();
    std::vector<User> opers = channel.getOperators();

    if (opers.size() > 0) {
        msg += "@" + opers[0].getNickname();

        for (size_t i = 1; i < opers.size(); i++)
            msg += " @" + opers[i].getNickname();

        for (size_t i = 0; i < users.size(); i++)
            msg += " " + users[i].getNickname();
    } else if (users.size() > 0) {
        msg += users[0].getNickname();

        for (size_t i = 1; i < users.size(); i++)
            msg += " " + users[i].getNickname();
    }

    return CODE_MSG(RPL_NAMES_REPLY_CODE, nickname, msg);
}
