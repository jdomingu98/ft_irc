#ifndef JOIN_COMMAND_HPP
# define JOIN_COMMAND_HPP

# include <map>

# include "ICommand.hpp"

# include "Server.hpp"

# include "libsUtils.hpp"

/**
 * An ICommand implementation that is responsible for the binding and creation of a channel.
 * 
 */
class JoinCommand : public ICommand {
    private:
        std::map<std::string, std::string> _channels; //key: channelName, value: channelPassword

    public:
        JoinCommand(std::map<std::string, std::string> channelMap);
        ~JoinCommand();

        void execute(int clientFd);
};

#endif