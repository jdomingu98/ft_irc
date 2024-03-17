#ifndef CHANNEL_EXCEPTION_HPP
# define CHANNEL_EXCEPTION_HPP

# include <string>

/**
 * An exception that is thrown when a command fails to execute.
 */
class ChannelException : public std::exception {
    private:
        std::string _message;
    public:
        ChannelException(const std::string& msg) : _message(msg) {}
        ~ChannelException() throw() {}

        virtual const char* what() const throw() {
            return _message.c_str();
        }
};

#endif
