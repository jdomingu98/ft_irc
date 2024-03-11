#ifndef SERVER_EXCEPTION_HPP
# define SERVER_EXCEPTION_HPP

# include <string>

class ServerException : public std::exception {
    private:
        std::string _message;
    public:
        ServerException(const std::string& msg) : _message(msg) {}
        ~ServerException() throw() {}

        virtual const char* what() const throw() {
            return _message.c_str();
        }
};

#endif
