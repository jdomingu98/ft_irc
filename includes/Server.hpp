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
        std::string             _topic;

        // Singleton Pattern
        static Server           *_server;
        Server(const std::string port, const std::string password);

        // Server logic
        bool isValidPort(const std::string &port) const;
        void initServer();
        void listenClients();
        void handleNewConnection(int numFds);
        void handleExistingConnection(int fd);
        void closeConnections();

        // User Iterators
        std::vector<User>::iterator findUserByFd(int clientFd);
        std::vector<User>::const_iterator findUserByFd(int clientFd) const;
        std::vector<User>::iterator findUserByNickname(const std::string &nickname);
        std::vector<User>::const_iterator findUserByNickname(const std::string &nickname) const;

        // Channel Iterators
        std::vector<Channel>::iterator findChannel(const std::string &channelName);
        std::vector<Channel>::const_iterator findChannel(const std::string &channelName) const;

    public:
        ~Server();

        // Singleton Pattern
        static void init(std::string port, std::string password);
        static Server &getInstance();

        // User
        User        &getUserByFd(int clientFd);
        const User  &getUserByFd(int clientFd) const;
        User        &getUserByNickname(const std::string& nickname);
        bool        isNicknameInUse(const std::string& nickname) const;
        void        removeUser(int clientFd);
        void        attemptUserRegistration(int clientFd);

        // Channel
        std::vector<Channel> getChannels() const;
        Channel &getChannelByName(const std::string &channelName);
        bool    channelExists(const std::string &channelName) const;
        void    addChannel(Channel channel);
        void    removeChannel(std::string channelName);

        // Other Operations
        void    sendMessage(int clientFd, const std::string& message) const;
        bool    isValidPassword(const std::string& password) const;
};

#endif