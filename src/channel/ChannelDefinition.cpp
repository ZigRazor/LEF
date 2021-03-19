#include "ChannelDefinition.hpp"

namespace CHANNEL
{
    std::map <std::string, Channel*> ChannelDefinition::channelMap;    

    void ChannelDefinition::addChannelToMap(std::string channelName, std::string ip, unsigned int port){
        channelMap[channelName] = new Channel(ip, port);
    }
    const Channel* ChannelDefinition::getChannelByName(std::string channelName){
        if (channelMap.find(channelName) != channelMap.end()){
            return channelMap.at(channelName);
        }
        return nullptr;
    }
    
}