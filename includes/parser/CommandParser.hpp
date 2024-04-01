#ifndef COMMAND_PARSER_HPP
# define COMMAND_PARSER_HPP

# include "ICommand.hpp"
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
# include "ModeParser.hpp"

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
    
    public:
        static ICommand* parse(const std::string& command);
};

#endif