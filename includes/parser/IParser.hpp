#ifndef I_PARSER_HPP
# define I_PARSER_HPP

# include "libsUtils.hpp"
# include "ACommand.hpp"

class ACommand;

class IParser {
    public:
        virtual ACommand *parse(const std::vector<std::string>& tokens) = 0;
        virtual ~IParser() {}
};

#endif