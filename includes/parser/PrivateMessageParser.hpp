#ifndef PRIVATE_MESSAGE_PARSER_HPP
# define PRIVATE_MESSAGE_PARSER_HPP

# include "IParser.hpp"
# include "PrivateMessageCommand.hpp"

# include "libsUtils.hpp"

/**
 * A class that represents the parser for the private message command.
 */
class PrivateMessageParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif