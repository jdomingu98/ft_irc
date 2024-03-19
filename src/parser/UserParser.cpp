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
ICommand *UserParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 5)
        throw NeedMoreParamsException("USER");
    std::string username = tokens[1];
    std::string hostname = tokens[2];
    std::string serverName = tokens[3];
    std::string realName = tokens[4];
    // remove the ':' from the real name:
    realName = realName.substr(1);

    for (size_t i = 5; i < tokens.size(); i++)
        realName += " " + tokens[i];
    return new UserCommand(username, hostname, serverName, realName);
}