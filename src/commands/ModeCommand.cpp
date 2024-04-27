#include "ModeCommand.hpp"

/**
 * Construct a new ModeCommand.
 * 
 * @param plus Whether the mode is positive (+t, +o, ...) or negative (-t, -o, ...)
 * @param channel The channel to set the mode
 * @param modes The modes to set
 * @param modeParams The parameters of the mode
 * 
 */
ModeCommand::ModeCommand(bool plus, const std::string& channel, std::vector<Mode> modes, std::vector<std::string>& modeParams) :
    ACommand(true),
    _plus(plus),
    _showChannelModes(false),
    _channel(Server::getInstance().getChannelByName(channel)),
    _modes(modes),
    _modeParams(modeParams) {}

ModeCommand::ModeCommand(const std::string &channel) :
    ACommand(true),
    _plus(false),
    _showChannelModes(true),
    _channel(Server::getInstance().getChannelByName(channel)) {
        this->_modes = std::vector<Mode>();
        this->_modeParams = std::vector<std::string>();
    }

/**
 * Destroy the ModeCommand.
 */
ModeCommand::~ModeCommand() {}

/**
 * Execute the MODE command.
 * 
 * @param clientFd The socket file descriptor of the client
 * 
 * @throws `NotOnChannelException` if the user is not on the channel
 */
void ModeCommand::execute(int clientFd) {
    Server &server = Server::getInstance();
    User &me = server.getUserByFd(clientFd);
    if (_showChannelModes) {
        server.sendMessage(
            clientFd,
            ChannelModeIsResponse(me.getNickname(), _channel.getName(), _channel.getModes(), _channel.getModeParams()).getReply()
        );
        return ;
    }
    
    if (!me.isOnChannel(_channel.getName()))
        throw NotOnChannelException(_channel.getName());

    std::string flag = _plus ? "+" : "-";
    std::vector<std::string>::iterator paramIterator = _modeParams.begin();
    std::string param = NONE;
    for (size_t i = 0; i < _modes.size(); i++) {
        flag += _modes[i];
    
        if (ModeCommand::modeNeedsParam(_modes[i])) {
            if (paramIterator == _modeParams.end())
                throw NeedMoreParamsException("MODE");
            param = *(paramIterator++);
        }
        switch (_modes[i]) {
            case INVITE_ONLY:
                ModeCommand::inviteOnly();
                break;
            case TOPIC_PROTECTED:
                ModeCommand::topicProtected();
                break;
            case CHANNEL_KEY:
                ModeCommand::channelKey(param);
                break;
            case CHANNEL_OPERATOR:
                ModeCommand::channelOperator(me, param);
                break;
            case USER_LIMIT:
                ModeCommand::userLimit(param);
                break;
            default:
                throw UnknownModeException(std::string(1, _modes[i]));
        }
    }
    _channel.broadcastToChannel(
        CMD_MSG(me.getNickname(), me.getUsername(), me.getHostname(), MODE_MSG(_channel.getName(), flag, param))
    );
}

/**
 * Execute the invite only option of the MODE command.
 * 
 * Sets the channel as invite-only mode.
 */
void ModeCommand::inviteOnly() {
    _channel.setInviteOnly(_plus);
}

/**
 * Execute the topic option of the MODE command.
 * 
 * Sets the topic of the channel.
 */
void ModeCommand::topicProtected() {
    _channel.setTopicProtected(_plus);
}

/**
 * Execute the key option of the MODE command.
 * 
 * Sets the password of the channel.
 */
void ModeCommand::channelKey(const std::string & param) {
    if (_channel.isPasswordSet() && _plus)
        throw KeySetException(_channel.getName());
    if (_plus)
        _channel.setPassword(param);
    else
        _channel.unsetPassword();
}

/**
 * Execute the operator option of the MODE command.
 * 
 * Sets the user as an operator of the channel.
 */
void ModeCommand::channelOperator(const User &me, const std::string &param) {
    if (!_channel.isOper(me.getNickname()))
        throw ChanOPrivsNeededException(_channel.getName());
    if (!_channel.isUserInChannel(param))
        throw UserNotInChannelException(param, _channel.getName());
    if (_plus)
        _channel.makeUserAnOper(param);
    else
        _channel.makeOperAnUser(param);
}

/**
 * Execute the limit option of the MODE command.
 * 
 * Sets the limit of users in the channel.
 */
void ModeCommand::userLimit(const std::string & param) {
    if (!_plus) {
        _channel.setLimit(NO_LIMIT);
        return ;
    }

    if (!Utils::isNumber(param))
        return ;

    int numUsers = std::atoi(param.c_str());
    if (numUsers > MAX_CLIENTS)
        numUsers = MAX_CLIENTS;
    _channel.setLimit(numUsers);
}

/**
 * Check if a mode needs a parameter.
 * 
 * @param mode The mode to check
 * 
 * @return True if the mode needs a parameter, false otherwise
 */
bool ModeCommand::modeNeedsParam(Mode mode) {
    return (mode == CHANNEL_KEY && _plus)
        || mode == CHANNEL_OPERATOR
        || (mode == USER_LIMIT && _plus);
}