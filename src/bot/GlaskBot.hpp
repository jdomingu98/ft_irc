#ifndef GLASK_BOT_HPP
# define GLASK_BOT_HPP

# include <sstream>
# include <iostream>
# include <map>
# include "IRCClient.hpp"
# include "message/Message.hpp"
# include "response/ResponseBuilder.hpp"

# define BOT_NAME "glask"

/**
 * This class aims to provide a simple interface to interact with an IRC server.
 */
class GlaskBot : public IRCClient {
    private:
		    static std::vector<std::string> split(const std::string &response);
            std::map<std::string, std::string> welcomeMessages;
            void onPrivateMessage(const Message &message);
            void onJoin(const Message &message);
    public:
        GlaskBot(const std::string &address, int port, const std::string &password);
        virtual ~GlaskBot();
        void handleResponse(const Message &message);
        void setMessage(const std::string &channel, const std::string &message);
};

#endif