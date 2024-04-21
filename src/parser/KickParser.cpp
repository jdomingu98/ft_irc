#include "KickParser.hpp"

/**
 * Parses the KICK command.
 * 
 * The format of the KICK command is as follows:
 * 
 * Command: KICK
 * Parameters: <channel>{,<channel>} <user>{,<user>} [<comment>]
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @throws `BadChannelMaskException` if the channel mask is invalid.
 * @return The parsed command.
 */
ACommand *KickParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3 || tokens[1].empty() || tokens[2].empty())
        throw NeedMoreParamsException("KICK");

    std::vector<std::string> channels = split(tokens[1], ',');
    std::vector<std::string> usersList = split(tokens[2], ',');
    std::vector<User> users;
    
    for (size_t i = 0; i < channels.size(); i++) {
        if (channels[i][0] != '#' && channels[i][0] != '&')
            throw BadChannelMaskException(channels[i]);
    }

    for (size_t i = 0; i < usersList.size(); i++) {
        User &user = Server::getInstance().getUserByNickname(usersList[i]);
        users.push_back(user);
    }
    usersList.clear();

    if (channels.size() != users.size() && (channels.size() > 1 || users.size() > 1))
        throw NeedMoreParamsException("KICK");
    
    const std::string comment = tokens.size() > 3 ? tokens[3] : NONE;

    return new KickCommand(channels, users, comment);
}