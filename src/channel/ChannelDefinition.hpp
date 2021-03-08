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
            static std::map <std::string, Channel*> channelMap;
        public:
            
            ChannelDefinition() = delete;
            ~ChannelDefinition() = delete;
            static void addChannelToMap(std::string channelName, std::string ip, unsigned int port);
            static const Channel* const getChannelByName(std::string channelName);
    };
}

#endif