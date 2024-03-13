#include"QuitParser.hpp"

ICommand *QuitParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() != 1)
        throw ParserException("QUIT COMMAND: Invalid number of arguments.");

    return new QuitCommand();
}