#ifndef COMMAND_NOT_FOUND_EXCEPTION_HPP
# define COMMAND_NOT_FOUND_EXCEPTION_HPP

# include <exception>

/**
 * This exception is thrown when a command is not found.
 */
class CommandNotFoundException : public std::exception {
    public:
        CommandNotFoundException() {}
        ~CommandNotFoundException() throw() {}

        const char *what() const throw() {
            return "Error: Command not found!";
        }
};

#endif