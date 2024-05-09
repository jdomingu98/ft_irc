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
 * @return The parsed command.
 */
ACommand* NoticeParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3)
        throw NeedMoreParamsException(NOTICE);
    return new NoticeCommand(Utils::split(tokens[1], ','), tokens[2]);
}