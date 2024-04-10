#ifndef PART_COMMAND_HPP
# define PART_COMMAND_HPP

# include "ACommand.hpp"

# include "Server.hpp"

# include "libsUtils.hpp"

class Channel;

/**
 * An ACommand implementation that is responsible for the leaving of a channel.
 * 
 */
class PartCommand : public ACommand {
    private:
        std::vector<std::string> _channels;

    public:
        PartCommand(std::vector<std::string> channels);
        ~PartCommand();

        void execute(int clientFd);
};

#endif