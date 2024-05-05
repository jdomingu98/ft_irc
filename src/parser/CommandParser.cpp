#include "CommandParser.hpp"

/**
 * Parses the command.
 * 
 * @param input The command to parse.
 * @param client The client that sent the command.
 * 
 * @return The parsed command.
 */
ACommand* CommandParser::parse(const std::string& input, const User *client) {
    std::string command(input);
    CommandParser::validateUserPrefix(command, client);
    std::vector<std::string> tokens = CommandParser::tokenize(command);

    if (tokens.empty())
        throw IgnoreCommandException();

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
    if (command == QUIT)
        return new QuitParser();
    if (command == PASS)
        return new PassParser();
    if (command == USER)
        return new UserParser();
    if (command == NICK)
        return new NickParser();
    if (command == PRIVMSG)
        return new PrivateMessageParser();
    if (command == JOIN)
        return new JoinParser();
    if (command == INVITE)
        return new InviteParser();
    if (command == PART)
        return new PartParser();
    if (command == TOPIC)
        return new TopicParser();
    if (command == KICK)
        return new KickParser();
    if (command == MODE)
        return new ModeParser();
    if (command == NOTICE)
        return new NoticeParser();
#ifdef BONUS
    if (command == WHO)
        return new WhoParser();
    if (command == DOWN)
        return new DownParser();
    if (command == UP)
        return new UpParser();
#endif
    if (command == NONE)
        throw IgnoreCommandException();
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
    // Split first by ":" if there is
    const size_t posColon = command.find(':');

    if (posColon == std::string::npos)
        return Utils::split(command, ' ');

    std::vector<std::string> tokens(Utils::split(command.substr(0, posColon), ' '));
    tokens.push_back(command.substr(posColon + 1));
    return tokens;
}

/**
 * This function asserts that the user prefix is correct.
 * If the prefix is incorrect, an exception is thrown.
 * When the prefix is detected, it is removed from the command to avoid parsing it at command level.
 * 
 * Format: nick [!user] [@hostname]
 * 
 * @param command The command to validate.
 * @param client The client that sent the command.
 * 
 * @throws `IgnoreCommandException` if the prefix is incorrect.
 * 
 */
void CommandParser::validateUserPrefix(std::string &command, const User *client) {
    if (command.empty())
        throw IgnoreCommandException();

    if (command[0] != ':')
        return;

    if (command.size() < 2)
        throw IgnoreCommandException();

    const size_t spaceIndex = command.find(' ');

    if (spaceIndex + 1 >= command.size())
        throw IgnoreCommandException();
    
    const std::string prefix = spaceIndex == std::string::npos
            ? command.substr(1)
            : command.substr(1, spaceIndex - 1);

    // Remove the prefix from the command for further parsing
    command = command.substr(spaceIndex + 1);

    const size_t userIndex = prefix.find('!');
    const size_t hostIndex = prefix.find('@');
    const bool hasUser = userIndex != std::string::npos;
    const bool hasHostname = hostIndex != std::string::npos;

    // Nick parsing
    std::string nick = prefix;

    if (hasUser)
        nick = prefix.substr(0, userIndex);
    else if (hasHostname)
        nick = prefix.substr(0, hostIndex);

    if (nick.empty())
        throw IgnoreCommandException();

    // Username parsing
    std::string username(NONE);
    if (hasUser) {
        if (hasHostname)
            username = prefix.substr(userIndex + 1, hostIndex - userIndex - 1);
        else
            username = prefix.substr(userIndex + 1);
    }

    // Hostname parsing
    const std::string hostname = hasHostname ? prefix.substr(hostIndex + 1) : NONE;

    if (nick != client->getNickname()
		|| (hasUser && username != client->getUsername())
		|| (hasHostname && hostname != client->getHostname()))
        throw IgnoreCommandException();
}

/**
 * Joins the vector of strings.
 * 
 * @param msg The vector of strings to be joined.
 * @param initialMsgPosition The position where the message begins
 * 
 * @return The joined string.
 */
const std::string CommandParser::join(const std::vector<std::string> &msg, size_t initialMsgPosition) {
    if (msg.empty() || initialMsgPosition >= msg.size())
        return NONE;
    
    const std::vector<std::string> msgTokens(msg.begin() + initialMsgPosition, msg.end());
    std::string strJoined;

    if (msgTokens.empty())
        return NONE;

    strJoined = msgTokens[0];
    if (strJoined.size() > 0 && strJoined[0] == ':') {
        for (size_t i = 1; i < msgTokens.size(); i++)
            strJoined += " " + msgTokens[i];
        strJoined = strJoined.substr(1);
    }
    return strJoined;
}