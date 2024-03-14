#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "User.hpp"

#include "ChannelException.hpp"

#include "libsUtils.hpp"

class Channel {
    private:
        std::string         _name;
        std::vector<User>   _users;
        std::string         _topic;
        char                _mode;

        std::vector<User>::iterator findUser(std::string nickname);
    
    public:
        Channel(std::string name);
        ~Channel();

        void addUser(User user); //JOIN #channel
        void removeUser(std::string nickname); //PART #channel


        //Getters
        std::string getName();
        std::vector<User> getUsers();
        std::string getTopic(); //TOPIC #channel
        char getMode(); //MODE #channel

        //Setters
        void setTopic(std::string topic); //TOPIC #channel :new topic
        void setMode(char mode); //MODE #channel <args>

};

#endif