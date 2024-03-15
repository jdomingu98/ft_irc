#ifndef NICK_PARSER_HPP
# define NICK_PARSER_HPP

# include "IParser.hpp"

# include "NickCommand.hpp"

# include "libsUtils.hpp"

/**
 * An IParser implementation that is responsible for parsing the NICK command.
 */
class NickParser : public IParser {
    public:
        ICommand *parse(const std::vector<std::string>& tokens);
};

#endif