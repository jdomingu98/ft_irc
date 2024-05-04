#ifndef WHO_COMMAND_HPP
# define WHO_COMMAND_HPP

#include "Server.hpp"

/**
 * An ACommand implementation that is responsible for querying the server for a list of users.
 */
class WhoCommand : public ACommand {
    private:
        const std::string _query;
        const bool        _hasOperatorFlag;

        void getQueryOfChannel(int clientFd, const Channel &channel);
    public:
        WhoCommand();
        WhoCommand(const std::string &query, const bool hasOperatorFlag);

        void execute(int clientFd);
};

#endif