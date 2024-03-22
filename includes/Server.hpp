#ifndef SERVER_HPP
# define SERVER_HPP

# include <arpa/inet.h>
# include <netinet/in.h>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>

# include "ICommand.hpp"
# include "CommandParser.hpp"

# include "Channel.hpp"
# include "User.hpp"

# include "libsUtils.hpp"

# define MIN_PORT 1
# define MAX_PORT 65535

# define BUFFER_SIZE 512
# define MAX_CLIENTS 42

class User;
class Channel;

/**
 * A class that represents the server.
 */
class Server {

    private:
        uint16_t                _port;
        std::string             _password;
        int                     _socketFd;
        struct sockaddr_in      _serverAddr;
        struct pollfd           _fds[MAX_CLIENTS];
        std::vector<User>       _users;
        std::vector<Channel>    _channels;

        bool isValidPort(const std::string port);
        void initServer();
        void listenClients();
        void handleNewConnection(int numFds);
        void handleExistingConnection(int fd);
        void closeConnections();
        std::vector<User>::iterator findUserByFd(int clientFd);
        std::vector<User>::iterator findUserByNickname(std::string nickname);
        std::vector<Channel>::iterator findChannel(std::string channelName);

    public:
        Server(const std::string port, const std::string password);
        ~Server();

        void sendMessage(int clientFd, const std::string& message) const;
        bool isValidPassword(const std::string& password);
        User &getUserByFd(int clientFd);
        User &getUserByNickname(const std::string& nickname);
        bool isNicknameInUse(const std::string& nickname);
        bool userHasCheckedPassword(int clientFd);
        void removeUser(int clientFd);
        void attemptUserRegistration(int clientFd);

        void addChannel(Channel channel);
        std::vector<Channel> getChannels() const;
        void removeChannel(std::string channelName);
};

#endif