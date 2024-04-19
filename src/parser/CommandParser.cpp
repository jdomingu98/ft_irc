#include "CommandParser.hpp"

/**
 * Parses the command.
 * 
 * @param input The command to parse.
 * @param client The client that sent the command.
 * 
 * @return The parsed command.
 */
ACommand* CommandParser::parse(const std::string& input, const User &client) {
    std::vector<std::string> tokens = split(input, ' '); //CommandParser::tokenize(input);
    if (tokens.size() >= 2 && tokens[0][0] == ':')
    {
        std::string nickname = client.getNickname();
        if (tokens[0].substr(1) != nickname && tokens[0] != USER_ID(nickname, client.getUsername(), client.getHostname())) {
            // throw new IRCException();
        }
        tokens.erase(tokens.begin());
    }

    IParser *parser = CommandParser::getParser(tokens[0]);
    if (!parser)
        return NULL;
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
    if (command == NONE)
        return NULL;
    throw UnknownCommandException(command);
}

/**
 * Tokenizes the command.
 * 
 * @param command The command to tokenize.
 * 
 * @return The tokens of the command.
 */
/*std::vector<std::string> CommandParser::tokenize(const std::string& command) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(command);
    
    while (std::getline(tokenStream, token, ' ')) {
        if (token.empty())
            continue;
        tokens.push_back(trim(token));
    }
    return tokens;
}*/