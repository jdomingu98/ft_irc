#include "ServerException.hpp"

ServerException::ServerException(const std::string& msg) : _message(msg) {}

const char* ServerException::what() const throw() {
    return _message.c_str();
}