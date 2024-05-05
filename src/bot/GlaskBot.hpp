#ifndef GLASK_BOT_HPP
# define GLASK_BOT_HPP

# include <sstream>
# include <iostream>
# include "IRCClient.hpp"
# include "message/Message.hpp"
# include "response/ResponseBuilder.hpp"

class GlaskBot : public IRCClient {
    private:
		static std::vector<std::string> split(const std::string &response);
    public:
        GlaskBot(const std::string &address, int port);
        ~GlaskBot();
        void handleResponse(const Message &message);
};

#endif