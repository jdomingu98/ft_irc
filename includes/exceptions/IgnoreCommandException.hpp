#ifndef IGNORE_COMMAND_EXCEPTION_HPP
# define IGNORE_COMMAND_EXCEPTION_HPP

# define IGN_CMD_MSG "This command is ignored."

class IgnoreCommandException : public std::exception {
    public:
        IgnoreCommandException() {}
        virtual ~IgnoreCommandException() throw() {}

        virtual const char* what() const throw() {
            return IGN_CMD_MSG;
        }
};

#endif