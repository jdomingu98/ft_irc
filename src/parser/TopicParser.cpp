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
ICommand *TopicParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException("TOPIC");
    Channel &channel = Server::getInstance().getChannelByName(tokens[1]);
    if (tokens.size() == 2 || isOnlySpaces(tokens)){
        Logger::debug("TOPIC without comment");
        return new TopicCommand(&channel);
    }
    if (!isColon(tokens))
        throw NeedMoreParamsException("TOPIC");
    Logger::debug("TOPIC with comment");
    return new TopicCommand(&channel, join(tokens));
}