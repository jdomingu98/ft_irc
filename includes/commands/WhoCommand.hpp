#ifndef WHO_COMMAND_HPP
# define WHO_COMMAND_HPP

#include "Server.hpp"

/**
 * An ACommand implementation that is responsible for querying the server for a list of users.
 */
class WhoCommand : public ACommand {
    private:
        std::string _query;
        bool        _hasOperatorFlag;

    public:
        WhoCommand();
        WhoCommand(std::string query, bool hasOperatorFlag);
        ~WhoCommand();

        void execute(int clientFd);
};

#endif