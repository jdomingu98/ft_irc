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
        throw NeedMoreParamsException("TOPIC");
    
    Channel &channel = Server::getInstance().getChannelByName(tokens[1]);
    if (tokens.size() == 2 || haveOnlySpaces(tokens))
        return new TopicCommand(&channel);

    Logger::debug("Calling TopicCommand to change the topic of channel " + tokens[1]);
    return new TopicCommand(&channel, isColonPresent(tokens) ? join(tokens, 2) : tokens[2]);
}