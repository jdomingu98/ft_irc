#include"QuitParser.hpp"

ICommand *QuitParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() > 2)
        throw ParserException("QUIT COMMAND: Invalid number of arguments.");
    if(tokens.size() == 2)
        return new QuitCommand(tokens[1]);
    return new QuitCommand();
}