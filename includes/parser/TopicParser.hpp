#ifndef TOPICPARSER_HPP
# define TOPICPARSER_HPP

# include "Channel.hpp"
# include "ICommand.hpp"
# include "IParser.hpp"
# include "libsUtils.hpp"
# include "TopicCommand.hpp"


class TopicParser : public IParser {
    public:
        ICommand *parse(const std::vector<std::string>& tokens);
};

#endif