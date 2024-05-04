#ifndef UP_COMMAND_HPP
# define UP_COMMAND_HPP

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for upload a file from a channel.
 * 
 */
class UpCommand : public ACommand {
    private:
        const std::string _channelName;
        const std::string _path;

    public:
        UpCommand(const std::string &channelName, const std::string &path);

        void execute(int clientFd);
};

#endif