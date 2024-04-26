#ifndef A_COMMAND_HPP
# define A_COMMAND_HPP

# include "Responses.hpp"

/**
 * An abstract class which represents a command that can be executed by the server.
 */
class ACommand {
    protected:
        bool _needsValidation;
    public:
        virtual void execute(int clientFd) = 0;
        ACommand(bool needValidate);

        bool needsValidation();
};

#endif