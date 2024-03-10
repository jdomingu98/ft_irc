#include <string>

class ServerException;

class ServerException : public std::exception {
    private:
        std::string _message;
    public:
        ServerException(const std::string& msg) : _message(msg) {}

        virtual const char* what() const throw() {
            return _message.c_str();
        }
};