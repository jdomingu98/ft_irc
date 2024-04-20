#include "UserParser.hpp"

/**
 * Parses the USER command.
 * 
 * The format of the USER command is as follows:
 * 
 * Command: USER
 * Parameters: <username> <hostname> <server name> :<real name which can contain spaces>
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @return The parsed command.
 */
ACommand *UserParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 5)
        throw NeedMoreParamsException("USER");

    return new UserCommand(tokens[1], tokens[2], tokens[3], tokens[4]);
}