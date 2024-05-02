#ifndef DOWN_COMMAND_HPP
# define DOWN_COMMAND_HPP

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for download a file from a channel.
 * 
 */
class DownCommand : public ACommand {
    private:
        std::string _channelName;
        std::string _filename;

    public:
        DownCommand(const std::string &channelName, const std::string &filename);
        ~DownCommand();

        void execute(int clientFd);
};

#endif