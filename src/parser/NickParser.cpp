#include "NickParser.hpp"

ACommand *NickParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() != 2)
        throw ParserException("NICK COMMAND: Invalid number of arguments.");

    return new NickCommand(tokens[1]);
}