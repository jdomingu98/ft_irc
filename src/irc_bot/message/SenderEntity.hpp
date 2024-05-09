#ifndef SENDER_ENTITY_HPP
# define SENDER_ENTITY_HPP

# include <string>
# include "../MalformedException.hpp"

class SenderEntity {
	private:
		bool _isServer;
		std::string _serverName;
		std::string _nickname;
		std::string _username;
		std::string _hostname;

	public:
		SenderEntity(const std::string &senderData);

		bool isServer() const;
		const std::string &getServerName() const;
		const std::string &getNickname() const;
		const std::string &getHostname() const;
		const std::string &getUsername() const;
};

#endif