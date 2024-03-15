#ifndef PASS_COMMAND_HPP
# define PASS_COMMAND_HPP

# include "ICommand.hpp"

# include "Server.hpp"

# include "libsUtils.hpp"

/**
 * An ICommand implementation that is responsible for validating the server connection.
*/
class PassCommand : public ICommand {
    private:
        std::string _password;
    
    public:
        PassCommand();
        PassCommand(const std::string& password);
        ~PassCommand();

        void execute(Server &server, int fd);
};

#endif