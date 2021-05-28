#include "Channel.hpp"
namespace CHANNEL
{
    Channel::Channel(const std::string& channelName, E_CommunicationType communicationType, const std::string& IP, unsigned int port)
    {
        this->channelName = channelName;
        this->communicationType = communicationType;
        this->IP = IP;
        this->port = port;
    }

    Channel::~Channel()
    {
    }

    const std::string& Channel::GetChannelName() const{
        return channelName;
    }

    Channel::E_CommunicationType Channel::GetCommunicationType() const{
        return communicationType;
    }

    std::string Channel::GetIP() const
    {
        return IP;
    }
    unsigned int Channel::GetPort() const
    {
        return port;
    }
}