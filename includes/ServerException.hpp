#include <string>

class ServerException : public std::exception {
    private:
        std::string _message;
    public:
        ServerException(const std::string& msg);

        virtual const char* what() const throw();
};