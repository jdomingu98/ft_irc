#include "NickParser.hpp"

/**
 * Parses the NICK command.
 * 
 * The format of the NICK command is as follows:
 * 
 * Command: NICK
 * Parameters: <nickname>
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NoNicknameGivenException` if the nickname is not specified.
 * @return The parsed command.
 */
ICommand *NickParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NoNicknameGivenException();
    return new NickCommand(tokens[1]);
}