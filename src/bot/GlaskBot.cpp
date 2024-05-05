#include "GlaskBot.hpp"

/**
 * GlaskBot constructor
 * 
 * @param address The address of the server
 * @param port The port of the server
 */
GlaskBot::GlaskBot(const std::string &address, int port) : IRCClient(address, port) {
    this->sendData("PASS 1111");
    this->sendData("NICK glask");
    this->sendData("USER glask * * :Glask Bot");
	// this->sendData("JOIN #test");
    this->startLoop();
}

/**
 * GlaskBot destructor
 */
GlaskBot::~GlaskBot() {}

/**
 * This function aims to handle the response from the server.
 * 
 * @param response The response from the server.
 */
void GlaskBot::handleResponse(const Message &message) {
	const SenderEntity *sender = message.getSender();
	if (sender->isServer()) {

	} else {
		if (message.getCommand() == "PRIVMSG") {
			std::string destination = sender->getNickname();
			const std::string &params = message.getParams();
			std::vector<std::string> messageParts = GlaskBot::split(params);
			std::cout << "Message: " << messageParts[1] << std::endl;
			if (messageParts[1] == ":!join") {
				this->sendData(ResponseBuilder::privmsg(destination, "Joining channel " + messageParts[2]));
				this->sendData(ResponseBuilder::join(messageParts[2]));
			}
		}
	}
}

std::vector<std::string> GlaskBot::split(const std::string &s) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, ' '))
        if (!item.empty())
            elems.push_back(item);
    return elems;
}