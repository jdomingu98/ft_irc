#include "TopicParser.hpp"

/**
 * Parses the TOPIC command.
 * 
 * The format of the TOPIC command is as follows:
 * 
 * Command: TOPIC
 * Parameters: <channel> [<topic>]
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @return The parsed command.
 */
ACommand *TopicParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException(TOPIC);
    
    Channel *channel = Server::getInstance().getChannelByName(tokens[1]);

    if (tokens.size() == 2)
        return new TopicCommand(channel);

    return new TopicCommand(channel, tokens[2]);
}