#include "InviteParser.hpp"

/**
 * Parses the INVITE command.
 * 
 * The format of the INVITE command is as follows:
 * 
 * Command: INVITE
 * Parameters: <nickname> <channel>
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @return The parsed command.
 */
ACommand *InviteParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3)
      throw NeedMoreParamsException("INVITE");
    return new InviteCommand(tokens[1], tokens[2]);
}