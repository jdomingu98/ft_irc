#ifndef PASS_COMMAND_HPP
# define PASS_COMMAND_HPP

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for validating the server connection.
 * 
 */
class PassCommand : public ACommand {
    private:
        const std::string _password;
    
    public:
        PassCommand(const std::string& password);

        void execute(int clientFd);
};

#endif