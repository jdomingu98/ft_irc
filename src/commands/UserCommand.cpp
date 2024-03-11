#include "commands/UserCommand.hpp"

/**
 * Command User default constructor
 * 
*/
UserCommand::UserCommand(): _username(""), _hostname(""), _serverName(""), _realName("") {}

/**
 * Command User constructor
 * 
 * @param username The username
 * @param hostname The hostname
 * @param serverName The server name
 * @param realName The real name of the client
*/
UserCommand::UserCommand(const std::string& username, const std::string& hostname, const std::string& serverName,
                            const std::string& realName) : _username(username), _hostname(hostname),
                                                            _serverName(serverName), _realName(realName) {}

/**
 * Command User destructor
 * 
 */
UserCommand::~UserCommand() {}

/**
 * Execute the command User.
 * Method inherited from ICommand
 */
void UserCommand::execute() {
    std::cout << "Username: " << _username << std::endl;
    std::cout << "Hostname: " << _hostname << std::endl;  
    std::cout << "Server name: " << _serverName << std::endl;  
    std::cout << "Real name: " << _realName << std::endl;
}
