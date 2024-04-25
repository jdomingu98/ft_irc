#ifndef A_RESPONSE_HPP
# define A_RESPONSE_HPP

# include "Server.hpp"

class Response {
    protected:
        std::string _codeNumber;
        std::string _nickname;
    public:
        Response(std::string codeNumber, std::string nickname);
        virtual ~Response();
        virtual std::string getResponse() const = 0;
};

#endif