#include "StartingInformationRequest_Msg.hpp"
#include "channel/ChannelDefinition.hpp"

namespace MESSAGES
{
    StartingInformationRequest_Msg::StartingInformationRequest_Msg()
    {
        MSG_CHANNEL = "InfoExchange_Channel";
    }

    StartingInformationRequest_Msg::~StartingInformationRequest_Msg()
    {
    }

    bool StartingInformationRequest_Msg::SerializeToOstream(std::ostream *output) const
    {
        header.SerializeToOstream(output);
        return true;
    }

    bool StartingInformationRequest_Msg::ParseFromIstream(std::istream *input)
    {
        header.ParseFromIstream(input);
        return true;
    }

    void StartingInformationRequest_Msg::FillHeader(const std::string senderIP)
    {
        header.SetCurrentTime();
        header.SetMessageId(MSG_ID);
        header.SetSenderIP_s(senderIP); //To Set Sender IP
        if (CHANNEL::ChannelDefinition::getChannelByName(MSG_CHANNEL))
        {
            header.SetReceiverIP_s(CHANNEL::ChannelDefinition::getChannelByName(MSG_CHANNEL)->GetIP());
            header.SetReceiverPort(CHANNEL::ChannelDefinition::getChannelByName(MSG_CHANNEL)->GetPort());
        }
        else
        {
            //ERROR
        }
        header.SetDataSize(0);
    }

    

}