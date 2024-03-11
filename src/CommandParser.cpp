#include "CommandParser.hpp"

ICommand* CommandParser::parse(const std::string& input) {
    std::cout << "INPUT" << input << "..." << std::endl;
    std::vector<std::string> tokens = CommandParser::tokenize(input);
    IParser *parser = CommandParser::getParser(tokens[0]);
    ICommand *command = parser->parse(tokens);
    delete parser;
    return command;
}

IParser* CommandParser::getParser(std::string command) {
    // Add here the commands
    std::cout << "?COMMAND: " << command << ".........";
    if (command == "USER\r\n") {
        std::cout << "HOLA???";
        return new UserParser();
    }
    throw CommandException("Invalid command received from client.");
}

std::vector<std::string> CommandParser::tokenize(const std::string& command) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(command);
    while (std::getline(tokenStream, token, ' ')) {
        std::cout << "HOLA?!!! " << token << ",,,,,,,,,,,,,,,,," << std::endl;
        tokens.push_back(token);
    }
    std::cout << "ASASASASASA: " << tokens[0] << ":::::" << std::endl;
    return tokens;
}
