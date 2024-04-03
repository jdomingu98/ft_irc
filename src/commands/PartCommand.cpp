#include "PartCommand.hpp"

/**
 * Constructs a new PartCommand.
 * 
 * @param channels The vector of channels to be left.
 */
PartCommand::PartCommand(std::vector<std::string> channels) : ICommand(true), _channels(channels) {}

/**
 * Destroys the PartCommand.
 */
PartCommand::~PartCommand() {
    this->_channels.clear();
}

/**
 * Executes the command PART.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NoSuchChannelException` if the channel does not exist.
 * @throws `NotOnChannelException` if the user is not on the channel.
 * 
 */
void PartCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);
    
    std::string nickname = user.getNickname();
    std::string username = user.getUsername();
    std::string hostname = user.getHostname();

    for (size_t i = 0; i < this->_channels.size(); i++) {
        
        Channel &channel = server.getChannelByName(this->_channels[i]);
	
        if (!user.isOnChannel(this->_channels[i]))
            throw NotOnChannelException(this->_channels[i]);

        Logger::debug("User in channel " + this->_channels[i] + ". Added to PART list.");

        channel.removeUser(nickname);

        std::vector<User> users = channel.getAllUsers();
        std::cout << "Users size: " << users.size() << std::endl;
        for (size_t j = 0; j < users.size(); j++) {
            Logger::debug("Sending PART message of user " + nickname + " to user " + users[j].getNickname().c_str());
            server.sendMessage(users[j].getFd(), PART_MSG(nickname, username, hostname, it->getName()));
        }
        users.clear();
    }
}