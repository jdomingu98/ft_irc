#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "../libsUtils.hpp"
# include "ICommand.hpp"
# include "../Server.hpp"
# include "CommandException.hpp"


class NickCommand: public ICommand
{
   private:
      std::string _nickname;

      bool isValidNickname();

    public:
        NickCommand();
        NickCommand(const std::string& nickname);
        void execute(Server &server, int fd);
        ~NickCommand(); 
};

#endif