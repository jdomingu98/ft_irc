#ifndef SERVER_HPP
# define SERVER_HPP

# include "libsUtils.hpp"

class Server {

    private:
        uint16_t _port;
        std::string _password;
    public:
        Server();
        ~Server();
};


#endif