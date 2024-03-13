#include "PassParser.hpp"

/**
 * Parses the PASS command.
 * 
 * The format of the PASS command is as follows:
 * 
 * Command: PASS
 * Parameters: <password>
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `ParserException` if the number of arguments is different than the expected.
 * @return The parsed command.
 */
ICommand* PassParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() != 2) {
        throw ParserException(MISSING_PARAMS_ERR);
    }
    return new PassCommand(tokens[1]);
}