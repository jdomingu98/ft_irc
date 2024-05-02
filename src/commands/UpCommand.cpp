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
 * UpCommand destructor.
 */
UpCommand::~UpCommand() {}

/**
 * Execute the command UP.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NotOnChannelException` If the user is not on the channel where it is trying to download the file.
 */
void UpCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &me = server.getUserByFd(clientFd);

    std::string filename = this->_path.substr(this->_path.find_last_of("/") + 1);

    if (!me.isOnChannel(this->_channelName))
        throw NotOnChannelException(this->_channelName);
    Channel &channel = server.getChannelByName(this->_channelName);
    channel.uploadFile(this->_path);

    std::vector<User *> users = channel.getAllUsers();
    for (size_t i = 0; i < users.size(); i++) {
        server.sendMessage(users[i]->getFd(), 
            CMD_MSG(me.getNickname(),
                    me.getUsername(),
                    me.getHostname(),
                    UP_MSG(me.getNickname(), filename, this->_channelName)
            )
        );
    }
}