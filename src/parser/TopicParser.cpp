#include"TopicParser.hpp"

/**
 * This function aims to parse the TOPIC command.
 * 
 * @param tokens The tokens to be parsed.
 * 
 * @return The parsed TOPIC command.
 */
ICommand *TopicParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException("TOPIC");
    if (tokens.size() == 2)
        return new TopicCommand(tokens[1]);
    return new TopicCommand(tokens[1], join(tokens));
}