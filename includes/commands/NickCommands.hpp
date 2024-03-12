#ifndef NICKCOMMANDS_HPP
# define NICKCOMMANDS_HPP

# include "../libsUtils.hpp"
# include "ICommand.hpp"
# include "../Server.hpp"

class Server;

class NickCommands : public ICommand
{
   private:
      std::string _nickname;
    public:
        NickCommands();
        NickCommands(const std::string& nickname);
        void execute(Server &server, int fd);
        ~NickCommands(); 
};

#endif