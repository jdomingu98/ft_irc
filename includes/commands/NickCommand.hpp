#ifndef NICKCOMMAND_HPP
# define NICKCOMMAND_HPP

# include "../libsUtils.hpp"
# include "ACommand.hpp"
# include "../Server.hpp"

class Server;

class NickCommand : public ACommand
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