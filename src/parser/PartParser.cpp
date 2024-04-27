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
        throw NeedMoreParamsException("PART");

    std::vector<std::string> channels = Utils::getInstance().split(tokens[1], ',');

    for (size_t i = 0; i < channels.size(); i++) {
        if (channels[i][0]  != '#' && channels[i][0] != '&')
            throw BadChannelMaskException(channels[i]);
    }

    return new PartCommand(channels);
}