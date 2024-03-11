#include "commands/UserCommand.hpp"

UserCommand::UserCommand(): _username(""), _hostname(""), _serverName(""), _realName("") {}

UserCommand::UserCommand(const std::string& username, const std::string& hostname, const std::string& serverName, const std::string& realName):
    _username(username), _hostname(hostname), _serverName(serverName), _realName(realName) {}

UserCommand::~UserCommand() {}

void UserCommand::execute() {
    std::cout << "Username: " << _username << std::endl;
    std::cout << "Hostname: " << _hostname << std::endl;  
    std::cout << "Server name: " << _serverName << std::endl;  
    std::cout << "Real name: " << _realName << std::endl;
}
