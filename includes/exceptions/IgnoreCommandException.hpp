#ifndef IGNORE_COMMAND_EXCEPTION_HPP
# define IGNORE_COMMAND_EXCEPTION_HPP

# include <exception>

class IgnoreCommandException : public std::exception {
    public:
        IgnoreCommandException() {}
        ~IgnoreCommandException() throw() {}

        virtual const char* what() const throw() {
            return "This command is ignored.";
        }
};

#endif