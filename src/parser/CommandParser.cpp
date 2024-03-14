#include "CommandParser.hpp"

/**
 * Parses the command.
 * 
 * @param input The command to parse.
 * 
 * @return The parsed command.
 */
ICommand* CommandParser::parse(const std::string& input, int fd, Server &server) {
    std::vector<std::string> tokens = CommandParser::tokenize(input);
    IParser *parser = CommandParser::getParser(tokens[0], fd, server);
    ICommand *command = parser->parse(tokens);
    delete parser;
    return command;
}

/**
 * Gets the corresponding parser object.
 * 
 * @param command The command to parse
 * 
 * @throws `CommandException` if the command is invalid
 * @return The parser for the command
 */
IParser* CommandParser::getParser(std::string command, int fd, Server &server) {
    if (command == "QUIT")
        return new QuitParser();
    if (command == "PASS")
        return new PassParser();
    if (!server.userHasCheckedPassword(fd))
        throw CommandException("User has not checked password.");
    if (command == "USER")
        return new UserParser();
    if (command == "NICK")
        return new NickParser();
    
    throw CommandException(INVALID_COMMAND);
}

/**
 * Tokenizes the command.
 * 
 * @param command The command to tokenize.
 * 
 * @return The tokens of the command.
 */
std::vector<std::string> CommandParser::tokenize(const std::string& command) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(command);
    
    while (std::getline(tokenStream, token, ' ')) {
        tokens.push_back(trim(token));
    }
    
    return tokens;
}