#include "parser/UserParser.hpp"

ICommand *UserParser::parse(const std::vector<std::string>& tokens) {
    // User command format: USER <username> <hostname> <server name> :<real name which can contain spaces>
    if (tokens.size() < 5) {
        throw ParserException("USER COMMAND: Invalid number of arguments.");
    }
    std::string username = tokens[1];
    std::string hostname = tokens[2];
    std::string serverName = tokens[3];
    std::string realName = tokens[4];
    for (size_t i = 5; i < tokens.size(); i++) {
        realName += " " + tokens[i];
    }
    return new UserCommand(username, hostname, serverName, realName);
}