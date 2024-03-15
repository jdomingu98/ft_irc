#ifndef IRC_EXCEPTION_HPP
# define IRC_EXCEPTION_HPP

# include <string>

/**
 * Generic Exception class for the IRC server.
 */
class IRCException : public std::exception {
    private:
        std::string _errorCode;
        std::string _message;

    public:
        IRCException(std::string errorCode, const std::string& msg): _errorCode(errorCode), _message(msg) {}
        ~IRCException() throw() {}

        virtual const char* what() const throw() {
            return _message.c_str();
        }

        std::string getErrorCode() const {
            return _errorCode;
        }
};

#endif