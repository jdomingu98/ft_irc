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
    if (tokens.size() < 3)
        throw NeedMoreParamsException("KICK");
    
    if (tokens[1].empty() || tokens[2].empty())
        throw NeedMoreParamsException("KICK");

    Server &server = Server::getInstance();
    std::vector<std::string> channelsList = split(tokens[1], ',');
    std::vector<std::string> usersList = split(tokens[2], ',');
    std::vector<Channel> channels;
    std::vector<User> users;
    
    for (size_t i = 0; i < channelsList.size(); i++) {
        if (channelsList[i][0] != '#' && channelsList[i][0] != '&')
            throw BadChannelMaskException(channelsList[i]);
        
        Channel &channel = server.getChannelByName(channelsList[i]);
        channels.push_back(channel);
    }

    for (size_t i = 0; i < usersList.size(); i++) {
        User &user = server.getUserByNickname(usersList[i]);
        users.push_back(user);
    }
    
    const std::string &comment = (tokens.size() >= 4) ? join(tokens, 4) : NONE;
    channelsList.clear();
    usersList.clear();
    return new KickCommand(channels, users, comment);
}