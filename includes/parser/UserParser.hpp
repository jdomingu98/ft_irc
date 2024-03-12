#ifndef USER_PARSER_HPP
# define USER_PARSER_HPP

# include "IParser.hpp"
# include "libsUtils.hpp"
# include "commands/UserCommand.hpp"
# include "exceptions/ParserException.hpp"

class UserParser: public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif