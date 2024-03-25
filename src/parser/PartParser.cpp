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

    std::vector<std::string> channelNameList = split(tokens[1], ',');
    std::vector<Channel> channels;
    std::vector<std::string> serverChannels = server.getChannels();
    std::vector<std::string> userChannels = user.getChannels();

    for (size_t i = 0; i < channelNameList.size(); i++) {
        //Search channels
        if (channelNameList[i]  != '#' || channelNameList[i] != '&') { //Probar que devuelve server oficial
            //throw IRCException();
        }

        //Comprobar qué se valida primero
        if (server.findChannel(channelNameList[i]) == serverChannels.end())
            throw NoSuchChannelException(channelNameList[i]);

        if (!user.isOnChannel(channelNameList[i]))
            throw NotOnChannelException(channelNameList[i]);
            
        Logger::debug("User in channel. Added to PART list.");
        channels.push_back(*(server.findChannel(channelNameList[i])));
    }

    serverChannels.clear();
    userChannels.clear();

    return new PartCommand(channels);
}