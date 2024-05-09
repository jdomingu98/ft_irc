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
ACommand *JoinParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException(JOIN);

    std::map<std::string, std::string> channels;
    const std::vector<std::string> keys = Utils::split(tokens[1], ',');
    std::vector<std::string> values;

    if (tokens.size() == 3)
        values = Utils::split(tokens[2], ',');

    for (size_t i = 0; i < keys.size(); i++)
        channels[keys[i]] = !values.empty() && !values[i].empty() ? values[i] : NONE;
    return new JoinCommand(channels);
}