#include "IRCClient.hpp"
 
IRCClient::IRCClient(const std::string &address , int port)
    : _connectionEstablished(false), _address(address), port(port) {
    conn();
}

IRCClient::~IRCClient() {
    close(this->_sock);
}
 
/**
 * Connect to a host on a certain port number
 */
void IRCClient::conn() {
    if (this->_connectionEstablished)
      return ;

    this->_sock = socket(AF_INET , SOCK_STREAM , 0);
    if (this->_sock == -1) {
        std::cerr << "Could not create socket" << std::endl;
        return ;
    }

    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(this->_address.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    std::cout << "Socket created\n" << std::endl;
    if (connect(this->_sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        std::cerr << "connect failed. Error" << std::endl;
        return ;
    }
    this->_connectionEstablished = true;
    std::cout << "Connected\n";
}
 
/**
 * Send data to the connected host
 */
bool IRCClient::sendData(const std::string &data) {
    const std::string message = data + "\r\n";
    if(send(this->_sock, message.c_str(), message.size(), 0) < 0) {
        std::cout << "Send failed" << std::endl;
        return false;
    }
    std::cout << "Data send\n" << std::endl;
     
    return true;
}
 
/**
 * Receive data from the connected host
 */
void IRCClient::receive() {
    char buffer[BUFFER_SIZE];

    std::memset(buffer, '\0', BUFFER_SIZE);

    if (recv(this->_sock, buffer, BUFFER_SIZE, 0) < 0)
        std::cout << "recv failed" << std::endl;
    else {
        std::string message(buffer);
        size_t pos = message.find_first_of("\r\n");
        if (pos != std::string::npos)
            while (pos != std::string::npos) {
                handleResponse(Message(message));
                message = message.substr(pos + 2);
                pos = message.find_first_of("\r\n");
            }
    }
}

/**
 * Start the loop to receive data from the connected host
*/
void IRCClient::startLoop() {
    while (true) {
        receive();
    }
}
 