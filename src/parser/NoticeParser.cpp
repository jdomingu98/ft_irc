#include "NoticeParser.hpp"

/**
 * Parses the NOTICE command.
 * 
 * The format of the NOTICE command is as follows:
 * 
 * Command: NOTICE
 * Parameters: <nickname> <text>
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `IgnoreCommandException` if any parameter is missing.
 * @return The parsed command.
 */
ACommand* NoticeParser::parse(const std::vector<std::string>& tokens) {
    std::vector<std::string> receivers;

    if (tokens.size() < 3)
        throw IgnoreCommandException();
    receivers = Utils::split(tokens[1], ',');

    return new PrivateMessageCommand(receivers, tokens[2]);
}