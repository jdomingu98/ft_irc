#include "QuitCommand.hpp"

/**
 * QuitCommand message constructor.
 * 
 * @param message The message
 */
QuitCommand::QuitCommand(const std::string &message) : ACommand(false), _message(message) {}

/**
 * Execute the command QUIT.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 */
void QuitCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User *user = server.getUserByFd(clientFd);

    std::vector<Channel *> channels = user->getChannels();
    std::set<User *> users;

    if (user->isRegistered())
        users.insert(user);

    std::vector<Channel *>::iterator channelIt;
    for (channelIt = channels.begin(); channelIt != channels.end(); ++channelIt) {
        
        std::vector<User *> allUsers = (*channelIt)->getUsers();
        std::vector<User *>::iterator usersIt;
        for (usersIt = allUsers.begin(); usersIt != allUsers.end(); ++usersIt)
            users.insert(*usersIt);
    }

    const std::string &nickname = user->getNickname();
    std::set<User *>::iterator it;
    for (it = users.begin(); it != users.end(); it++) {
        server.sendMessage((*it)->getFd(), 
                            CMD_MSG(nickname, user->getUsername(), user->getHostname(),
                                    QUIT_MSG(_message.empty() ? nickname : _message)));
    }
    server.handleClientDisconnection(clientFd);
}