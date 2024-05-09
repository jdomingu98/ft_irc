#include "Message.hpp"

/**
 * Constructor for the Message class.
 * 
 * @param senderData The sender data.
 */
Message::Message(const std::string &message) {
	std::vector<std::string> messageParts = splitParams(message);
	if (messageParts.size() < 2)
		throw MalformedException("Message does not have enough params.");
	_sender = new SenderEntity(messageParts[0]);
	_command = messageParts[1];

	// TODO: if sender is the server, _param is containing also the client (me, the bot) nickname
	// at the beginning, so do we need to remove it?
	_params = message.substr(message.find(_command) + _command.size() + 1);
}

/**
 * Destructor for the Message class.
 */
Message::~Message() {
	delete _sender;
}

/**
 * Splits the string by the delimiter.
 * 
 * @param s The string to be split.
 * 
 * @return The vector of strings.
 */
std::vector<std::string> Message::splitParams(const std::string &s) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, ' '))
        if (!item.empty())
            elems.push_back(item);
    return elems;
}

/**
 * Returns the sender entity.
 * 
 * @return The sender entity.
 */
const SenderEntity *Message::getSender() const {
	return _sender;
}

/**
 * Returns the command.
 * 
 * @return The command.
 */
const std::string &Message::getCommand() const {
	return _command;
}

/**
 * Returns the params.
 * 
 * @return The params.
 */
const std::string &Message::getParams() const {
	return _params;
}
