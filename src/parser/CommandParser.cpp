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
    std::string command(input);
    CommandParser::validateUserPrefix(command, client);
    std::vector<std::string> tokens = CommandParser::tokenize(input);

    if (tokens.empty())
        return NULL;

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
std::vector<std::string> CommandParser::tokenize(const std::string& command) {
    
    std::vector<std::string> tokens(split(command, ' '));
    std::string token;
    
    for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); it++) {
        if (it->size() > 0 && it->at(0) == ':') {
            token = join(tokens, it - tokens.begin());
            *it = token;
            tokens.erase(it + 1, tokens.end());
            break;
        }
    }
    return tokens;
}

/**
 * This function asserts that the user prefix is correct.
 * If the prefix is incorrect, an exception is thrown.
 * When the prefix is detected, it is removed from the command to avoid parsing it at command level.
 * 
 * @param command The command to validate.
 * @param client The client that sent the command.
 * 
 * @throws `IRCException` if the prefix is incorrect.
 * 
 */
void CommandParser::validateUserPrefix(std::string &command, const User &client) {
    if (command.empty() || command[0] != ':')
        return;
    if (command.size() < 2)
        throw IRCException("-42", "IDK what error to throw here. I'm just a comment. I'm not even a real exception.");

    size_t spaceIndex = command.find(' ');
    std::string prefix(NONE);
    if (spaceIndex == std::string::npos)
        prefix = command.substr(1);
    else
        prefix = command.substr(1, command.find(' ') - 1);

    command = command.substr(spaceIndex + 1);

    size_t userIndex = prefix.find('!');
    size_t hostIndex = prefix.find('@');
    bool hasUser = userIndex != std::string::npos;
    bool hasHostname = hostIndex != std::string::npos;

    // Nick parsing
    std::string nick(NONE);
    if (hasUser) {
        nick = prefix.substr(0, userIndex);
    } else if (hasHostname) {
        nick = prefix.substr(0, hostIndex);
    } else {
        nick = prefix;
    }

    // Username parsing
    std::string username(NONE);
    if (hasUser) {
        if (hasHostname) {
            username = prefix.substr(userIndex + 1, hostIndex - userIndex - 1);
        } else {
            username = prefix.substr(userIndex + 1);
        }
    }

    // Hostname parsing
    std::string hostname(NONE);
    if (hasHostname) {
        hostname = prefix.substr(prefix.find('@') + 1);
    }
    if (nick != client.getNickname() || (hasUser && username != client.getUsername()) || (hasHostname && hostname != client.getHostname())) {
        throw IRCException("-42", "IDK what error to throw here. I'm just a comment. I'm not even a real exception.");
    }

}