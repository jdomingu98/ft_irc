#ifndef I_COMMAND_HPP
# define I_COMMAND_HPP

class Server;

/**
 * An interface that represents a command that can be executed by the server.
 */
class ICommand {
    protected:
        bool _needValidate;
    public:
        virtual void execute(int clientFd) = 0;
        ICommand(bool needValidate) : _needValidate(needValidate) {};
};

#endif