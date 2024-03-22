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
 * @return The parsed command.
 */
ICommand *JoinParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException("JOIN");

    std::map<std::string, std::string> channels;
    std::vector<std::string> channelsVec = split(tokens[1], ',');
    std::vector<std::string> keysVec = split(tokens[2], ',');

    for (size_t i = 0; i < channelsVec.size(); i++) {
        if (channelsVec[i] == "" && keysVec[i] == "")
            continue;
        if (channelsVec[i] == "") {}
            // throw IRCException();
        if (i < keysVec.size() && keysVec[i] != "")
            channels[channelsVec[i]] = keysVec[i];
        else
            channels[channelsVec[i]] = "";
    }
    channelsVec.clear();
    keysVec.clear();
    return new JoinCommand(channels);
}