#include "QuitCommand.hpp"

/**
 * QuitCommand message constructor.
 * 
 * @param msg The message
 */
QuitCommand::QuitCommand(std::string message) : ACommand(false), _message(message) {}

/**
 * QuitCommand destructor.
 */
QuitCommand::~QuitCommand() {}

/**
 * Execute the command QUIT.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 */
void QuitCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &user = server.getUserByFd(clientFd);

    std::string nickname = user.getNickname();
    std::vector<Channel> &channels = server.getChannels();
    
    int destFd;
    for (size_t i = 0; i < channels.size(); i++) {
        std::vector<User> usersChannel = channels[i].getAllUsers();

        for (size_t j = 0; j < usersChannel.size(); j++) {
            if (!channels[i].isUserInChannel(usersChannel[j].getNickname()))
                continue;
            destFd = usersChannel[j].getFd();
            if (server.isUserConnected(destFd)) {
                server.sendMessage(destFd, QUIT_MSG(nickname, user.getUsername(), user.getHostname(),
                                            _message.empty() ? nickname : _message));
            }
        }

        usersChannel.clear();
    }
    server.handleClientDisconnection(clientFd);
}