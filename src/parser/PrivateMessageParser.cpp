#include "PrivateMessageParser.hpp"

/**
 * Parses the private message command.
 * 
 * @param server the server
 * @param fd the file descriptor
 * @param message the message to parse with the following format: "PRIVMSG <receiver>[, <receiver>] :<message>"
*/
ICommand* PrivateMessageParser::parse(const std::vector<std::string>& tokens) {
    if (tokens.size() < 3) {
        throw NoRecipientGivenException("PRIVMSG");
    }
    std::vector<std::string> receivers;
    std::string message;

    std::string receiver = tokens[1];
    receivers.push_back(receiver);
    size_t i = 2;
    while (i < tokens.size() && tokens[i][0] != ':') {
        receivers.push_back(tokens[i]);
        i++;
    }
    if (i == tokens.size()) {
        throw NoTextToSendException();
    }
    message = tokens[i].substr(1);
    for (size_t j = i + 1; j < tokens.size(); j++) {
        message += " " + tokens[j];
    }

    return new PrivateMessageCommand(receivers, message);
}
