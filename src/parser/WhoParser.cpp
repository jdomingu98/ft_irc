#include "WhoParser.hpp"

/**
 * Parses the WHO command.
 * 
 * The format of the WHO command is as follows:
 * 
 * Command: WHO
 * Parameters: [<name> [<o>]]
 * 
 * @param tokens The parameters of the command.
 * 
 * @return The parsed command.
 */
ACommand *WhoParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2 || (tokens.size() == 2 && tokens[1] == "0"))
        return new WhoCommand();
    return new WhoCommand(tokens[1], tokens.size() > 2 && tokens[2] == "o");
}