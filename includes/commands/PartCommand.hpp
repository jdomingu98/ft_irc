#ifndef PART_COMMAND_HPP
# define PART_COMMAND_HPP

# include "Server.hpp"

/**
 * An ACommand implementation that is responsible for the leaving of a channel.
 * 
 */
class PartCommand : public ACommand {
    private:
        const std::vector<std::string> _channels;

    public:
        PartCommand(const std::vector<std::string> channels);

        void execute(int clientFd);
};

#endif