#include "PartCommand.hpp"

/**
 * Constructs a new PartCommand.
 * 
 * @param channels The vector of channels to be left.
 */
PartCommand::PartCommand(std::vector<Channel> channels) : ICommand(true), _channels(channels) {}

/**
 * Destroys the PartCommand.
 */
PartCommand::~PartCommand() {
    this->_channels.clear();
}

/**
 * Executes the command PART.
 * 
 * @param server The server where the command will be executed
 * @param clientFd The socket file descriptor of the client
 * 
 */
void PartCommand::execute(Server &server, int clientFd) {
    User user = server.getUserByFd(clientFd);

    std::string nickname = user.getNickname();
    std::string username = user.getUsername();
    std::string hostname = user.getHostname();

    for (size_t i = 0; i < this->_channels.size(); i++) {
        this->_channels[i].removeUser(nickname);
        std::vector<User> users = this->_channels[i].getUsers();
        for (size_t j = 0; j < users.size(); j++) {
            Logger::debug("Sending PART message of user " + nickname + " to user " + users[j].getNickname().c_str());
            server.sendMessage(users[j].getFd(), PART_MSG(nickname, username, hostname, this->_channels[i].getName()));
        }
        users.clear();
    }
}