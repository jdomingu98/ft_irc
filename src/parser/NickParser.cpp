#include "NickParser.hpp"

ICommand *NickParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() != 2 || tokens[1].empty())
        throw ParserException("NICK COMMAND: Invalid number of arguments or empty nickname.");

    if (server.isNicknameInUse(tokens[1]))
        throw ParserException("NICK COMMAND: Nickname is already in use.");

    for(size_t i = 0; i < tokens[1].size(); i++) {
        if ((!std::isalnum(tokens[1][i]) && tokens[1][i] != '_' ) || tokens[1][i] == ' ' || tokens[1][i] == '\r' || tokens[1][i] == '\n')
            throw ParserException("NICK COMMAND: Invalid nickname.");
    }
    return new NickCommand(tokens[1]);
}