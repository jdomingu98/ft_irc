#ifndef COMMAND_PARSER_HPP
# define COMMAND_PARSER_HPP

# include "InviteParser.hpp"
# include "IParser.hpp"
# include "JoinParser.hpp"
# include "KickParser.hpp"
# include "ModeParser.hpp"
# include "NickParser.hpp"
# include "PartParser.hpp"
# include "PassParser.hpp"
# include "PrivateMessageParser.hpp"
# include "QuitParser.hpp"
# include "TopicParser.hpp"
# include "UserParser.hpp"
# include "NoticeParser.hpp"

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