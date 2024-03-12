#ifndef COMMAND_PARSER_HPP
# define COMMAND_PARSER_HPP

# include "libsUtils.hpp"
# include "ACommand.hpp"
# include "UserCommand.hpp"
# include "exceptions/CommandException.hpp"
# include "IParser.hpp"
# include "UserParser.hpp"
# include "PassParser.hpp"
# include "NickParser.hpp"

class CommandParser {
    public:
        static ACommand* parse(const std::string& command);

    private:
        static std::vector<std::string> tokenize(const std::string& command);
        static IParser* getParser(std::string command);
};

#endif