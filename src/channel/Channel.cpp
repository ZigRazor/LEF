#include "Channel.hpp"
namespace CHANNEL
{
    Channel::Channel(E_CommunicationType communicationType, std::string IP, unsigned int port)
    {
        this->communicationType = communicationType;
        this->IP = IP;
        this->port = port;
    }

    Channel::~Channel()
    {
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