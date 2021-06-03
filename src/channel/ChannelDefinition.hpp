#ifndef CHANNELDEFINITION_H
#define CHANNELDEFINITION_H
#pragma once
#include "channel/Channel.hpp"
#include <map>

namespace CHANNEL
{
    class ChannelDefinition
    {
    private:
        static std::map<std::string, Channel *> channelNameMap;
        static std::map<std::pair<std::string, unsigned int>, Channel *> channelAddressMap;

    public:
        ChannelDefinition() = delete;
        ~ChannelDefinition() = delete;
        static void addChannelToMap(std::string channelName, Channel::E_CommunicationType communicationType, std::string ip, unsigned int port);
        static const Channel *getChannelByName(std::string channelName);
        static const Channel *getChannelByAddress(const std::string &ip, const unsigned int port);
    };
}

#endif