#include "ModeCommand.hpp"

ModeCommand::ModeCommand(bool plus, const std::string& channel, std::vector<Mode> modes, const std::string& modeParams)
  : ICommand(true), _plus(plus), _channel(channel), _modes(modes), _modeParams(modeParams) {}

ModeCommand::~ModeCommand() {}

void ModeCommand::execute(int clientFd) {
    Server server = Server::getInstance();
    User me = server.getUserByFd(clientFd);
    Channel channel = server.getChannelByName(_channel);
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

void ModeCommand::inviteOnly() {
  Server::getInstance().getChannelByName(_channel).setInviteOnly(_plus);
}

void ModeCommand::topicProtected() {
  Server::getInstance().getChannelByName(_channel).setTopicProtected(_plus);
}

void ModeCommand::channelKey() {
    Channel &channel = Server::getInstance().getChannelByName(_channel);
    if (_plus)
        channel.setPassword(_modeParams);
    else
        channel.unsetPassword();
}

void ModeCommand::channelOperator() {
    Channel &channel = Server::getInstance().getChannelByName(_channel);
    if (!channel.isUserInChannel(_modeParams)) {}
        // Throw something
    if (_plus)
        channel.makeUserAnOper(_modeParams);
    else
        channel.makeOperAnUser(_modeParams);
}

void ModeCommand::userLimit() {
    Channel &channel = Server::getInstance().getChannelByName(_channel);
    int numUsers = _plus ? std::atoi(_modeParams.c_str()) : NO_LIMIT;
    channel.setLimit(numUsers);
}
