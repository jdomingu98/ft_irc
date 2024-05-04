#include "UpCommand.hpp"

/**
 * UpCommand constructor.
 * 
 * @param channelName The channel name
 * @param path The path of the file to upload
 */
UpCommand::UpCommand(const std::string& channelName, const std::string& path)
    : ACommand(true), _channelName(channelName), _path(path) {}

/**
 * Execute the command UP.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NotOnChannelException` If the user is not on the channel where it is trying to download the file.
 */
void UpCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User *me = server.getUserByFd(clientFd);

    const std::string &filename = _path.substr(_path.find_last_of("/") + 1);
    const std::string &nickname = me->getNickname();

    if (!me->isOnChannel(_channelName))
        throw NotOnChannelException(_channelName);
    Channel &channel = server.getChannelByName(_channelName);
    channel.uploadFile(_path);

    std::vector<User *> users = channel.getAllUsers();
    std::vector<User *>::iterator userIt;
    for (userIt = users.begin(); userIt != users.end(); ++userIt) {
        server.sendMessage((*userIt)->getFd(), 
            CMD_MSG(nickname, me->getUsername(), me->getHostname(),
                UP_MSG(nickname, filename, _channelName)
            )
        );
    }
}