#include"TopicParser.hpp"

ICommand *TopicParser::parse(const std::vector<std::string>& tokens) {
    if(tokens.size() < 2)
        throw NeedMoreParamsException("TOPIC");
    if(tokens.size() == 2)
        return new TopicCommand(tokens[1]);
    return new TopicCommand(tokens[1],join(tokens));
}