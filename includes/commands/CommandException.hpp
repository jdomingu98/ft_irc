#ifndef COMMAND_EXCEPTION_HPP
# define COMMAND_EXCEPTION_HPP

# include <string>

class CommandException: public std::exception {
    private:
        std::string _message;
    public:
        CommandException(const std::string& msg) : _message(msg) {}
        ~CommandException() throw() {}

        virtual const char* what() const throw() {
            return _message.c_str();
        }
};

#endif
