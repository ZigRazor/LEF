#include "LeaderAlive_Msg.hpp"
#include "channel/ChannelDefinition.hpp"

namespace MESSAGES
{
    
    LeaderAlive_Msg::LeaderAlive_Msg()
    {
        MSG_CHANNEL = "Leader_Channel";
    }

    LeaderAlive_Msg::~LeaderAlive_Msg()
    {
    }

    bool LeaderAlive_Msg::SerializeToOstream(std::ostream* output) const
    {
        header.SerializeToOstream(output);
        return true;
    }

	bool LeaderAlive_Msg::ParseFromIstream(std::istream* input)
    {
        header.ParseFromIstream(input);
        return true;
    }

    void LeaderAlive_Msg::FillHeader(std::string senderIP)
    {
        header.SetCurrentTime();
        header.SetMessageId(MSG_ID);
        header.SetSenderIP_s(senderIP); //To Set Sender IP
        if(CHANNEL::ChannelDefinition::getChannelByName(MSG_CHANNEL)){
            header.SetReceiverIP_s(CHANNEL::ChannelDefinition::getChannelByName(MSG_CHANNEL)->GetIP());
            header.SetReceiverPort(CHANNEL::ChannelDefinition::getChannelByName(MSG_CHANNEL)->GetPort());
        }else{
            //ERROR
        }
        header.SetDataSize(0);
    }

}