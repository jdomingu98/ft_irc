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
    if (tokens.size() == 2){
        std::cout << "TOPIC == 2" << std::endl;
        Channel channel = Server::getInstance().getChannelByName(tokens[1]);
        std::cout << "parse topic channnel " << channel.getName() << std::endl;
        return new TopicCommand(tokens[1], channel.getTopic());
    }
    return new TopicCommand(tokens[1], join(tokens));
}