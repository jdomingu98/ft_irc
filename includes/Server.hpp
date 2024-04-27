#ifndef SERVER_HPP
# define SERVER_HPP

# include <arpa/inet.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <poll.h>
# include <sys/socket.h>
# include <sys/types.h>

# include "ACommand.hpp"
# include "CommandParser.hpp"

# include "Channel.hpp"
# include "User.hpp"

# include "Utils.hpp"

# define MIN_PORT 1
# define MAX_PORT 65535

# define BUFFER_SIZE 512
# define MAX_CLIENTS 42

# define NONE ""

class Channel;

class User;

/**
 * A class that represents the server.
 */
class Server {

    private:
        uint16_t                    _port;
        std::string                 _password;
        int                         _socketFd;
        struct sockaddr_in          _serverAddr;
        struct pollfd               _fds[MAX_CLIENTS];
        int                         _numFds;
        std::map<int, std::string>  _inputBuffer;
        std::vector<User>           _users;
        std::vector<Channel>        _channels;
        Utils&                      utils;

        // Singleton Pattern
        static Server           *_server;
        Server(const std::string port, const std::string password);

        // Signal Handler
        bool _signalReceived;

        // Server logic
        bool isValidPort(const std::string &port) const;
        void initServer();
        void listenClients();
        void handleNewConnection();
        void handleExistingConnection(int clientFd);

        // User Iterators
        std::vector<User>::iterator findUserByFd(int clientFd);
        std::vector<User>::const_iterator findUserByFd(int clientFd) const;
        std::vector<User>::iterator findUserByNickname(const std::string &nickname);
        std::vector<User>::const_iterator findUserByNickname(const std::string &nickname) const;


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
        std::vector<Channel> &getChannels();
        Channel &getChannelByName(const std::string &channelName);
        bool    channelExists(const std::string &channelName) const;
        void    addChannel(Channel channel);
        void    removeChannel(std::string channelName);

        // Disconnection
        bool    isUserConnected(int clientFd) const;
        void    handleClientDisconnection(int clientFd);
        void	closeConnections();

        // Other Operations
        void    sendMessage(int clientFd, const std::string& message) const;
        void    sendExceptionMessage(int clientFd, const IRCException &e) const;
        bool    isValidPassword(const std::string& password) const;
        void	setSignalReceived();

        // Channel Iterators
        std::vector<Channel>::iterator findChannel(const std::string &channelName);
        std::vector<Channel>::const_iterator findChannel(const std::string &channelName) const;
};

void signalHandler(int signal);

#endif