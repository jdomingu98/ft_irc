#include "Responses.hpp"

/**
 * Returns the RPL_NAMES_REPLY message.
 * 
 * @param channelName The name of the channel
 * @param opers The vector of operators in the channel
 * @param users The vector of users in the channel
 * 
 * @return The RPL_NAMES_REPLY message
 */
std::string NamesReplyResponse::rplNamesReply(Channel &channel) const {
    std::vector<User> users = channel.getUsers();
    std::vector<User> opers = channel.getOperators();
    
    std::string msg = channel.getName() + " :";
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
    return msg;
}