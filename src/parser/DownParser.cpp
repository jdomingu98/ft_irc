#include "DownParser.hpp"

/**
 * Parses the DOWN command.
 * 
 * The format of the DOWN command is as follows:
 * 
 * Command: DOWN
 * Parameters: <channel> <filename>
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @throws `NoSuchChannelException` if the channel is not found.
 * 
 * @return The parsed command.
 */
ACommand *DownParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3)
        throw NeedMoreParamsException(DOWN);
    
    if (!Server::getInstance().channelExists(tokens[1]))
        throw NoSuchChannelException(tokens[1]);

    return new DownCommand(tokens[1], tokens[2]);
}