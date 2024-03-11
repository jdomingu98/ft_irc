#include "CommandParser.hpp"

ICommand* CommandParser::parse(const std::string& input) {
    std::vector<std::string> tokens = CommandParser::tokenize(input);
    IParser *parser = CommandParser::getParser(tokens[0]);
    ICommand *command = parser->parse(tokens);
    delete parser;
    return command;
}

IParser* CommandParser::getParser(std::string command) {
    // Add here the commands
    // Change to switch??
    if (command == "USER")
        return new UserParser();
    if (command == "PASS")
        return new PassParser();
    throw CommandException("Invalid command received from client.");
}

std::vector<std::string> CommandParser::tokenize(const std::string& command) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(command);
    while (std::getline(tokenStream, token, ' ')) {
        tokens.push_back(trim(token));
    }
    return tokens;
}