#include "CommandParser.hpp"

/**
 * Parses the command.
 * 
 * @param input The command to parse.
 * 
 * @return The parsed command.
 */
ACommand* CommandParser::parse(const std::string& input) {
    std::vector<std::string> tokens = CommandParser::tokenize(input);
    IParser *parser = CommandParser::getParser(tokens[0]);
    try {
        ACommand *command = parser->parse(tokens);
        delete parser;
        return command;
    } catch (...) {
        delete parser;
        throw;
    }
}

/**
 * Gets the corresponding parser object.
 * 
 * @param command The command to parse
 * 
 * @throws `UnknownCommandException` if the command is invalid
 * @return The parser for the command
 */
IParser* CommandParser::getParser(std::string command) {
    if (command == "QUIT")
        return new QuitParser();
    if (command == "PASS")
        return new PassParser();
    if (command == "USER")
        return new UserParser();
    if (command == "NICK")
        return new NickParser();
    if (command == "PRIVMSG")
        return new PrivateMessageParser();
    if (command == "JOIN")
        return new JoinParser();
    if (command == "INVITE")
        return new InviteParser();
    if (command == "PART")
        return new PartParser();
    if (command == "TOPIC")
        return new TopicParser();
    if (command == "KICK")
        return new KickParser();
    if (command == "MODE")
        return new ModeParser();
    if (command != NONE)
        throw UnknownCommandException(command);
}

/**
 * Tokenizes the command.
 * 
 * @param command The command to tokenize.
 * 
 * @return The tokens of the command.
 */
std::vector<std::string> CommandParser::tokenize(const std::string& command) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(command);
    
    while (std::getline(tokenStream, token, ' ')) {
        if (token.empty())
            continue;
        tokens.push_back(trim(token));
    }
    return tokens;
}