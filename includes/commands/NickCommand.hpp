#ifndef NICK_COMMAND_HPP
# define NICK_COMMAND_HPP

# include "ACommand.hpp"

# include "Server.hpp"

# define MAX_NICKNAME_SIZE 9

/**
 * An ACommand implementation that is responsible for setting the nickname of an user.
 * 
*/
class NickCommand : public ACommand {
    private:
        std::string _nickname;

        bool isValidNickname();

    public:
        NickCommand();
        NickCommand(const std::string& nickname);
        ~NickCommand(); 

        void execute(int clientFd);
};

#endif