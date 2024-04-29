#include "QuitCommand.hpp"

/**
 * QuitCommand message constructor.
 * 
 * @param message The message
 */
QuitCommand::QuitCommand(const std::string &message) : ACommand(false), _message(message) {}

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
    
    std::set<User> allUsers;
    std::set<User>::iterator it;

    if (user.isRegistered())
        allUsers.insert(user);
    for (size_t i = 0; i < channels.size(); i++) {
        if (!channels[i].isUserInChannel(nickname))
            continue;

        std::vector<User> usersChannel = channels[i].getAllUsers();
        for (size_t j = 0; j < usersChannel.size(); j++)
            allUsers.insert(usersChannel[j]);
        usersChannel.clear();
    }

    for (it = allUsers.begin(); it != allUsers.end(); it++) {
        server.sendMessage(it->getFd(), 
                            CMD_MSG(nickname, user.getUsername(), user.getHostname(),
                                    QUIT_MSG(_message.empty() ? nickname : _message)));
    }
    server.handleClientDisconnection(clientFd);
}