#ifndef NICK_COMMAND_HPP
# define NICK_COMMAND_HPP

# include "ICommand.hpp"

# include "Server.hpp"

# include "CommandException.hpp"

# include "libsUtils.hpp"


# define MAX_NICKNAME_SIZE 9

/**
 * An ICommand implementation that is responsible for setting the nickname of an user.
 * 
*/
class NickCommand : public ICommand {
    private:
        std::string _nickname;

        bool isValidNickname();

    public:
        NickCommand();
        NickCommand(const std::string& nickname);
        ~NickCommand(); 

        void execute(Server &server, int fd);
};

#endif