#include "InviteCommand.hpp"

/**
 * InviteCommand default constructor.
 */
InviteCommand::InviteCommand() : ACommand(true), _nickname(NONE), _channelName(NONE) {}

/**
 * InviteCommand nickname and channel name constructor.
 * 
 * @param nickname The nickname
 * @param channelName The channel name
 */
InviteCommand::InviteCommand(const std::string& nickname, const std::string& channelName)
    : ACommand(true), _nickname(nickname), _channelName(channelName) {}

/**
 * InviteCommand destructor.
 */
InviteCommand::~InviteCommand() {}

/**
 * Execute the command INVITE.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NoSuchNickException` If the nickname is not in use
 * @throws `NotOnChannelException` If the user which invites is not on the channel
 * @throws `UserOnChannelException` If the user invited is already on the channel
 * @throws `ChanOPrivsNeededException` If the user which invites is not an operator of the channel and the channel is invite-only
 */
void InviteCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &me = server.getUserByFd(clientFd);

    if (!server.isNicknameInUse(this->_nickname))
        throw NoSuchNickException(this->_nickname);

    if (!me.isOnChannel(this->_channelName))
        throw NotOnChannelException(this->_channelName);

    Channel &channel = server.getChannelByName(this->_channelName);

    if (channel.isUserInChannel(this->_nickname))
        throw UserOnChannelException(this->_nickname, this->_channelName);

    if (channel.isInviteOnly() && !channel.isOper(me.getNickname()))
        throw ChanOPrivsNeededException(this->_channelName);

    channel.inviteUser(this->_nickname);
    server.sendMessage(clientFd, RPL_INVITING(this->_nickname,
                                                me.getUsername(),
                                                me.getHostname(),
                                                this->_channelName));
}