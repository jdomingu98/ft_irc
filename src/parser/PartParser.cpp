#include "PartParser.hpp"

/**
 * Parses the PART command.
 * 
 * The format of the PART command is as follows:
 * 
 * Command: PART
 * Parameters: <channel>{,<channel>}
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NeedMoreParamsException` if the number of arguments is less than the expected.
 * @throws `NoSuchChannelException` if the channel does not exist.
 * @throws `NotOnChannelException` if the user is not on the channel.
 * @return The parsed command.
 */
ICommand *PartParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NeedMoreParamsException("PART");

    std::vector<std::string> channels = split(tokens[1], ',');

    for (size_t i = 0; i < channels.size(); i++) {
        //Search channels
        if (channels[i]  != "#" || channels[i] != "&") { //Probar que devuelve server oficial
            //throw IRCException();
        }
    }

    return new PartCommand(channels);
}