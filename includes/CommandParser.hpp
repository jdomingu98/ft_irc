#ifndef COMMAND_PARSER_HPP
# define COMMAND_PARSER_HPP

# include "libsUtils.hpp"
# include "commands/ICommand.hpp"
# include "commands/UserCommand.hpp"
# include "commands/CommandException.hpp"
# include "parser/IParser.hpp"
# include "parser/UserParser.hpp"

class CommandParser {
    public:
        static ICommand* parse(const std::string& command);

    private:
        static std::vector<std::string> tokenize(const std::string& command);
        static IParser* getParser(std::string command);
};

#endif