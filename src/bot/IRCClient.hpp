#ifndef IRC_CLIENT_HPP
# define IRC_CLIENT_HPP

# include <iostream> 
# include <string>
# include <arpa/inet.h>
# include <cstring>
# include <unistd.h>
# include <vector>
# include "message/Message.hpp"

# define BUFFER_SIZE 1024

/**
 * TCP Client class
 */
class IRCClient {
    private:
        bool              _connectionEstablished;
        int               _sock;
        const std::string &_address;
        int               port;

        void conn();
        void receive();
      
    public:
        IRCClient(const std::string &, int);
        virtual ~IRCClient();
        bool sendData(const std::string &);
        void startLoop();

        virtual void handleResponse(const Message &message) = 0;
};

#endif