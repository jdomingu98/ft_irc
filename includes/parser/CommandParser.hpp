#ifndef COMMAND_PARSER_HPP
# define COMMAND_PARSER_HPP

# include "ACommand.hpp"
# include "IParser.hpp"

# include "UserCommand.hpp"
# include "UserParser.hpp"
# include "PassParser.hpp"
# include "NickParser.hpp"
# include "QuitParser.hpp"
# include "PrivateMessageParser.hpp"
# include "JoinParser.hpp"
# include "PartParser.hpp"
# include "InviteParser.hpp"
# include "TopicParser.hpp"
# include "ModeParser.hpp"
# include "KickParser.hpp"

# include "libsUtils.hpp"

/**
 * Enumerates the commands that the server can receive.
 */
enum Commands {
    USER,
    PASS,
    NICK,
    QUIT,
    JOIN,
    PART,
    PRIVMSG,
    TOPIC,
    MODE,
    KICK,
    INVITE,
    OPER
};

/**
 * A class that is responsible for parsing strings to commands.
 */
class CommandParser {
    private:
        static std::vector<std::string> tokenize(const std::string& command);
        static IParser* getParser(std::string command);
        static void validateUserPrefix(std::string& command, const User &client);
        static const std::string join(const std::vector<std::string> &msg, size_t initialMsgPosition);
    
    public:
        static ACommand* parse(const std::string& command, const User &client);
};

#endif