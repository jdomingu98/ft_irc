#include "PassParser.hpp"

ICommand* PassParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() != 2) {
        throw ParserException("Invalid number of arguments for pass command");
    }
    return new PassCommand(tokens[1]);
}