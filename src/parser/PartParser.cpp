#include "PartParser.hpp"

/**
 * Parses the PART command.
 * 
 * The format of the PART command is as follows:
 * 
 * Command: PART
 * Parameters: <channel>{,<channel>}
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @throws `BadChannelMaskException` if the channel mask is invalid.
 * @return The parsed command.
 */
ACommand *PartParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException(PART);

    std::vector<std::string> channels = Utils::split(tokens[1], ',');

    std::vector<std::string>::const_iterator it;
    for (it = channels.begin(); it != channels.end(); ++it) {
        if ((*it)[0] != '#' && (*it)[0] != '&')
            throw BadChannelMaskException(*it);
    }
    return new PartCommand(channels);
}