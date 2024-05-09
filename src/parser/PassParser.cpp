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
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @return The parsed command.
 */
ACommand* PassParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException(PASS);
    return new PassCommand(tokens[1]);
}