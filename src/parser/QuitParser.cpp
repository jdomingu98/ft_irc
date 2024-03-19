#include "QuitParser.hpp"

/**
 * Parses the QUIT command.
 * 
 * The format of the QUIT command is as follows:
 * 
 * Command: QUIT
 * Parameters: <message> (optional)
 * 
 * @param tokens The parameters of the command.
 * 
 * @return The parsed command.
 */
ICommand *QuitParser::parse(const std::vector<std::string>& tokens) {
    // TODO: fix bug: if the message contains spaces, it will be split into multiple tokens.
    // The message should be the concatenation of all the tokens after the command.
    if (tokens.size() == 2)
        return new QuitCommand(tokens[1]);
    return new QuitCommand();
}