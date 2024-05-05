#include "Responses.hpp"

/**
 * Returns the RPL_NAMES_REPLY message.
 * 
 * @param channel The channel where the reply occurs.
 * 
 * @return The RPL_NAMES_REPLY message
 */
std::string NamesReplyResponse::rplNamesReply(const Channel &channel) const {
    const std::vector<User *> users = channel.getUsers();
    const std::vector<User *> opers = channel.getOperators();
    
    std::string msg = "= " + channel.getName();
    msg.append(" :");
    if (!opers.empty()) {
        msg.append("@").append(opers[0]->getNickname());
    
        for (size_t i = 1; i < opers.size(); i++)
            msg.append(" @").append(opers[i]->getNickname());
    
        for (size_t i = 0; i < users.size(); i++)
            msg.append(" ").append(users[i]->getNickname());
    } else if (!users.empty()) {
        msg.append(users[0]->getNickname());
    
        for (size_t i = 1; i < users.size(); i++)
            msg.append(" ").append(users[i]->getNickname());
    }
    return msg;
}