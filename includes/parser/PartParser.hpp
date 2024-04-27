#ifndef PART_PARSER_HPP
# define PART_PARSER_HPP

# include "IParser.hpp"

# include "PartCommand.hpp"

# include "Utils.hpp"

/**
 * An IParser implementation that is responsible for parsing the PART command.
 */
class PartParser : public IParser {
    public:
        ACommand *parse(const std::vector<std::string>& tokens);
};

#endif