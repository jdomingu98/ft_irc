#include "JoinParser.hpp"

/**
 * Parses the JOIN command.
 * 
 * The format of the JOIN command is as follows:
 * 
 * Command: JOIN
 * Parameters: <channel>{,<channel>} [<key>{,<key>}]
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @throws `BadChannelMaskException` if the channel mask is invalid.
 * @return The parsed command.
 */
ACommand *JoinParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException("JOIN");

    Utils& utils = Utils::getInstance();
    std::map<std::string, std::string> channels;
    std::vector<std::string> channelsVec = utils.split(tokens[1], ',');
    std::vector<std::string> keysVec;

    if (tokens.size() == 3)
        keysVec = utils.split(tokens[2], ',');

    for (size_t i = 0; i < channelsVec.size(); i++) {
        if (channelsVec[i].empty())
            continue;

        if (channelsVec[i][0] != '#' && channelsVec[i][0] != '&')
            throw BadChannelMaskException(channelsVec[i]);
        
        channels[channelsVec[i]] = (!keysVec.empty() && !keysVec[i].empty()) ? keysVec[i] : NONE;
    }
    if (!keysVec.empty())
        keysVec.clear();
    channelsVec.clear();
    return new JoinCommand(channels);
}