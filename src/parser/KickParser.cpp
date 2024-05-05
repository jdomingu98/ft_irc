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
        throw NeedMoreParamsException(KICK);

    const std::vector<std::string> channels = Utils::split(tokens[1], ',');
    const std::vector<std::string> usersList = Utils::split(tokens[2], ',');
    
    std::vector<std::string>::const_iterator it;
    for (it = channels.begin(); it != channels.end(); ++it) {
        if ((*it)[0] != '#' && (*it)[0] != '&')
            throw BadChannelMaskException(*it);
    }

    std::vector<User *> users;
    std::vector<std::string>::const_iterator it2;
    for (it2 = usersList.begin(); it2 != usersList.end(); ++it2) {
        try {
            User *user = Server::getInstance().getUserByNickname(*it2);
            users.push_back(user);
        } catch (const NoSuchNickException& e) {
            Logger::debug("User not found!. Continue parsing KICK command.");
        }
    }

    if (channels.size() != users.size() && channels.size() != 1 && users.size() != 1)
        throw NeedMoreParamsException(KICK);

    return new KickCommand(channels, users, tokens.size() > 3 ? tokens[3] : NONE);
}