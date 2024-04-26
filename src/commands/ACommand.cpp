#include "ACommand.hpp"

/**
 * ACommand constructor.
 * 
 * @param needValidation If the command needs validation
*/
ACommand::ACommand(bool needsValidation) : _needsValidation(needsValidation) {}


/**
  * Getter for the needValidation attribute.
  * 
  * @return If the command needs validation
  */
bool ACommand::needsValidation() {
    return this->_needsValidation;
}

std::string NamesReplyResponse::rplNamesReply(Channel &channel) const {
    std::vector<User> users = channel.getUsers();
    std::vector<User> opers = channel.getOperators()
    
    std::string msg = " " + channel.getName() + " :";
    if (opers.size() > 0) {
        msg += "@" + opers[0].getNickname()
    
        for (size_t i = 1; i < opers.size(); i++)
            msg += " @" + opers[i].getNickname()
    
        for (size_t i = 0; i < users.size(); i++)
            msg += " " + users[i].getNickname();
    } else if (users.size() > 0) {
        msg += users[0].getNickname()
    
        for (size_t i = 1; i < users.size(); i++)
            msg += " " + users[i].getNickname();
    }
    return msg;
}