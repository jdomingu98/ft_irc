#include "PartCommand.hpp"

/**
 * Constructs a new PartCommand.
 * 
 * @param channels The vector of channels to be left.
 */
PartCommand::PartCommand(const std::vector<std::string> channels) : ACommand(true), _channels(channels) {}

/**
 * Executes the command PART.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NotOnChannelException` if the user is not on the channel.
 * @throws `NoSuchChannelException` if the channel does not exist.
 * 
 */
void PartCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User *user = server.getUserByFd(clientFd);

    const std::string nickname = user->getNickname();

    std::vector<std::string>::const_iterator chNamesIt;
    for (chNamesIt = _channels.begin(); chNamesIt != _channels.end(); ++chNamesIt) {
        const std::string name = *chNamesIt;
        try {
            Channel *channel = server.getChannelByName(name);
            
            if (!user->isOnChannel(name))
                throw NotOnChannelException(name);
            Logger::debug("User in channel " + name);

            std::vector<User *> allUsers = channel->getUsers();
            std::vector<User *>::iterator usersIt;
            Logger::debug("Sending PART message");
            for (usersIt = allUsers.begin(); usersIt != allUsers.end(); ++usersIt)
                server.sendMessage((*usersIt)->getFd(),
                    CMD_MSG(nickname, user->getUsername(), user->getHostname(),
                        PART_MSG(name)
                    )
                );

            channel->removeUser(nickname);
            Logger::debug("User " + nickname + " removed from channel " + name + ".");
        } catch (NoSuchChannelException &e) {
            Logger::debug("Channel " + name + " does not exist.");
            server.sendExceptionMessage(clientFd, e);
        }
    }
}