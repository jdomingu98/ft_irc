#include "SenderEntity.hpp"

SenderEntity::SenderEntity(const std::string &data) {
	std::string senderData = data;
	if (senderData[0] != ':')
		throw MalformedException("Sender data does not start with a colon.");
	senderData = senderData.substr(1);
	// if the sender data contains ! and @, it is a user
	size_t exclamationMark = senderData.find('!');
	size_t atSign = senderData.find('@');

	if (exclamationMark != std::string::npos
		&& atSign != std::string::npos) {
		_isServer = false;
		_nickname = senderData.substr(0, exclamationMark);
		_username = senderData.substr(exclamationMark + 1, atSign - exclamationMark - 1);
		_hostname = senderData.substr(atSign + 1);
		_serverName = "";
	} else {
		_isServer = true;
		_nickname = "";
		_username = "";
		_hostname = "";
		_serverName = senderData;
	}
}

bool SenderEntity::isServer() const {
	return _isServer;
}

const std::string &SenderEntity::getServerName() const {
	return _serverName;
}

const std::string &SenderEntity::getNickname() const {
	return _nickname;
}

const std::string &SenderEntity::getUsername() const {
	return _username;
}

const std::string &SenderEntity::getHostname() const {
	return _hostname;
}