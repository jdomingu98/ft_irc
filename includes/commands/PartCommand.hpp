#ifndef PART_COMMAND_HPP
# define PART_COMMAND_HPP

# include "ICommand.hpp"

# include "Server.hpp"
# include "Channel.hpp"

# include "libsUtils.hpp"
# include "utils.hpp"

class Channel;

/**
 * An ICommand implementation that is responsible for the leaving of a channel.
 * 
 */
class PartCommand : public ICommand {
    private:
        std::vector<Channel> _channels;

    public:
        PartCommand(std::vector<Channel> channels);
        ~PartCommand();

        void execute(Server &server, int clientFd);
};

#endif