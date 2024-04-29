#ifndef NOTICE_PARSER_HPP
# define NOTICE_PARSER_HPP

# include "IParser.hpp"
# include "NoticeCommand.hpp"

/**
 * A class that represents the parser for the notice command.
 */
class NoticeParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif