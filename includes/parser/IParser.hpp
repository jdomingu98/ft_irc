#ifndef I_PARSER_HPP
# define I_PARSER_HPP

# include "libsUtils.hpp"
# include "commands/ICommand.hpp"

class IParser {
    public:
        virtual ICommand *parse(const std::vector<std::string>& tokens) = 0;
        virtual ~IParser() {}
};

#endif