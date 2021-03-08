#include "Channel.hpp"  
namespace CHANNEL{
Channel::Channel(std::string IP, unsigned int port)
{
	this->IP = IP;
    this->port = port;
}
	
Channel::~Channel()
{
	
}

std::string Channel::GetIP() const {
    return IP;
}
unsigned int  Channel::GetPort() const {
    return port;
}
}