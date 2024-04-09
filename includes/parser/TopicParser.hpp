#ifndef TOPIC_PARSER_HPP
# define TOPIC_PARSER_HPP

# include "IParser.hpp"

# include "TopicCommand.hpp"

# include "Channel.hpp"

# include "libsUtils.hpp"


/**
 * An IParser implementation that is responsible for parsing the TOPIC command.
 */
class TopicParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif