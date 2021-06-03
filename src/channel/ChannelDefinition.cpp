#include "ChannelDefinition.hpp"

namespace CHANNEL
{
    std::map<std::string, Channel *> ChannelDefinition::channelNameMap;
    std::map<std::pair<std::string, unsigned int>, Channel *> ChannelDefinition::channelAddressMap;

    void ChannelDefinition::addChannelToMap(std::string channelName, Channel::E_CommunicationType communicationType, std::string ip, unsigned int port)
    {
        Channel *channel = new Channel(channelName, communicationType, ip, port);
        channelNameMap[channelName] = channel;
        channelAddressMap[std::pair<std::string, unsigned int>(ip, port)] = channel;
    }
    const Channel *ChannelDefinition::getChannelByName(std::string channelName)
    {
        if (channelNameMap.find(channelName) != channelNameMap.end())
        {
            return channelNameMap.at(channelName);
        }
        return nullptr;
    }

    const Channel *ChannelDefinition::getChannelByAddress(const std::string &ip, const unsigned int port)
    {
        std::pair<std::string, unsigned int> address(ip, port);
        if (channelAddressMap.find(address) != channelAddressMap.end())
        {
            return channelAddressMap.at(address);
        }
        return nullptr;
    }

}