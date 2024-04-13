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
ModeCommand::ModeCommand(bool plus, const std::string& channel, std::vector<Mode> modes, const std::string& modeParams)
    : ACommand(true), _plus(plus), _channel(channel), _modes(modes), _modeParams(modeParams) {}

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
    Channel &channel = server.getChannelByName(_channel);
    
    if (!me.isOnChannel(channel.getName()))
        throw NotOnChannelException(channel.getName());

    for (size_t i = 0; i < _modes.size(); i++) {
        switch (_modes[i]) {
            case INVITE_ONLY:
                ModeCommand::inviteOnly();
                break;
            case TOPIC_PROTECTED:
                ModeCommand::topicProtected();
                break;
            case CHANNEL_KEY:
                ModeCommand::channelKey();
                break;
            case CHANNEL_OPERATOR:
                if (!channel.isOper(me.getNickname()))
                    throw ChanOPrivsNeededException(_channel);
                ModeCommand::channelOperator();
                break;
            case USER_LIMIT:
                ModeCommand::userLimit();
                break;
            default:
                // Aquí habrá que hacer algo digo yo.
                // ¿Tú qué crees, compañero de la vida y del código fuente de este proyecto de POO en C++ que estamos haciendo juntos y que nos está quedando tan bonito?
                // ¿Qué crees que deberíamos hacer aquí en este switch que no tiene un caso por defecto y que no hace nada?
                // ¿Crees que deberíamos lanzar una excepción o algo así para que el programa no se quede colgado y no haga nada cuando se le pide que haga algo que no sabe hacer?
                // ¿O crees que deberíamos hacer algo más elegante y sofisticado que eso? ¿Qué opinas tú, compañero de fatigas y de código fuente de este proyecto de POO en C++ que estamos haciendo juntos y que nos está quedando tan bonito?
                // Comentario autoconversacional para rellenar espacio y hacer que este comentario sea más largo y parezca más interesante y útil de lo que realmente es.
                // Autogenerado por C++ AutoCommentator Pro 3000, el mejor generador de comentarios automáticos para C++ del mercado.
                break;
        }
    }
}

/**
 * Execute the invite only option of the MODE command.
 * 
 * Sets the channel as invite-only mode.
 */
void ModeCommand::inviteOnly() {
    Server::getInstance().getChannelByName(_channel).setInviteOnly(_plus);
}

/**
 * Execute the topic option of the MODE command.
 * 
 * Sets the topic of the channel.
 */
void ModeCommand::topicProtected() {
    Server::getInstance().getChannelByName(_channel).setTopicProtected(_plus);
}

/**
 * Execute the key option of the MODE command.
 * 
 * Sets the password of the channel.
 */
void ModeCommand::channelKey() {
    if (_modeParams == NONE && _plus)
        throw NeedMoreParamsException("MODE");
    Channel &channel = Server::getInstance().getChannelByName(_channel);
    if (_plus)
        channel.setPassword(_modeParams);
    else
        channel.unsetPassword();
}

/**
 * Execute the operator option of the MODE command.
 * 
 * Sets the user as an operator of the channel.
 */
void ModeCommand::channelOperator() {
    if (_modeParams == NONE)
        throw NeedMoreParamsException("MODE");
    Channel &channel = Server::getInstance().getChannelByName(_channel);
    if (!channel.isUserInChannel(_modeParams))
        throw UserNotInChannelException(_modeParams, _channel);
    if (_plus)
        channel.makeUserAnOper(_modeParams);
    else
        channel.makeOperAnUser(_modeParams);
}

/**
 * Execute the limit option of the MODE command.
 * 
 * Sets the limit of users in the channel.
 */
void ModeCommand::userLimit() {
    if (_modeParams == NONE && _plus)
        throw NeedMoreParamsException("MODE");
    if (!isNumber(_modeParams))
        return ;

    int numUsers = std::atoi(_modeParams.c_str());
    if (numUsers < 0 || numUsers > MAX_CLIENTS)
        numUsers = MAX_CLIENTS;
    Server::getInstance().getChannelByName(_channel).setLimit(_plus ? numUsers : NO_LIMIT);
}
