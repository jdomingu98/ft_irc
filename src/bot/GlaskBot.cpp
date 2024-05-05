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
void GlaskBot::handleResponse(const std::string &sender, const std::vector<std::string> &message) {
    std::cout <<  "Sender: " << sender << std::endl;
    std:: cout << "Command: " << message[0] << std::endl;
    for (size_t i = 1; i < message.size(); i++)
        std::cout << "Param " << i - 2 << ": " << message[i] << std::endl;
}
