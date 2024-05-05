#ifndef GLASK_BOT_HPP
# define GLASK_BOT_HPP

# include "IRCClient.hpp"

class GlaskBot : public IRCClient {
    private:
    public:
        GlaskBot(const std::string &address, int port);
        ~GlaskBot();
        void handleResponse(const std::string &nickname, const std::vector<std::string> &message);
};

#endif