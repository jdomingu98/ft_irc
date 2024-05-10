#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <vector>
# include <string>
# include <sstream>
# include <iostream>
# include "SenderEntity.hpp"

/**
 * This class represents a message received from an IRC server.
 */
class Message {
	private:
		SenderEntity *_sender;
		std::string _command;
		std::string _params;
  	    std::vector<std::string> splitParams(const std::string &response);

	public:
		Message(const std::string &senderData);
		~Message();
		const SenderEntity *getSender() const;
		const std::string &getCommand() const;
		const std::string &getParams() const;
};

#endif