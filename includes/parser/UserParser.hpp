#ifndef USER_PARSER_HPP
# define USER_PARSER_HPP

# include "IParser.hpp"

# include "UserCommand.hpp"

# include "Utils.hpp"

/**
 * An IParser implementation that is responsible for parsing the USER command.
 */
class UserParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif