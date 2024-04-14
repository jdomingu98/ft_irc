#include "QuitParser.hpp"

/**
 * Parses the QUIT command.
 * 
 * The format of the QUIT command is as follows:
 * 
 * Command: QUIT
 * Parameters: [<message>]
 * 
 * @param tokens The parameters of the command.
 * 
 * @return The parsed command.
 */
ACommand *QuitParser::parse(const std::vector<std::string>& tokens) {
    return new QuitCommand(tokens.size() > 1 ? join(tokens, 1) : NONE);
}