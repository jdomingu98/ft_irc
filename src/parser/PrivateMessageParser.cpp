#include "PrivateMessageParser.hpp"

/**
 * Parses the PRIVMSG command.
 * 
 * The format of the PRIVMSG command is as follows:
 * 
 * Command: PRIVMSG
 * Parameters: <receiver>{,<receiver>} :<text to be sent>
 * 
 * @param tokens The parameters of the command.
 * 
 * @throws `NoRecipientGivenException` if no recipient is given.
 * @throws `NoTextToSendException` if no text is given.
 * @return The parsed command.
 */
ACommand* PrivateMessageParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 2)
        throw NoRecipientGivenException(PRIVMSG);

    if (tokens.size() < 3)
        throw NoTextToSendException();

    return new PrivateMessageCommand(Utils::split(tokens[1], ','), tokens[2]);
}