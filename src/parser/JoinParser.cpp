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
    return new JoinCommand(tokens[1], tokens[2]);
}