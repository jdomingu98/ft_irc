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
 * @throws `ParserException` if the number of arguments is different than the expected.
 * @return The parsed command.
 */
ICommand *QuitParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() > 2)
        throw ParserException("QUIT COMMAND: Invalid number of arguments.");
    if (tokens.size() == 2)
        return new QuitCommand(tokens[1]);
    return new QuitCommand();
}