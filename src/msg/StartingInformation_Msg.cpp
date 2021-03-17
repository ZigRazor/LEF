#include "StartingInformation_Msg.hpp"
#include "channel/ChannelDefinition.hpp"
#include "MessageConstant.hpp"

namespace MESSAGES
{
    StartingInformation_Msg::StartingInformation_Msg()
    {
        MSG_CHANNEL = "InfoExchange_Channel";
    }

    StartingInformation_Msg::~StartingInformation_Msg()
    {
    }

    bool StartingInformation_Msg::SerializeToOstream(std::ostream *output) const
    {
        header.SerializeToOstream(output);
        *output << masterIP << FIELD_DELIMITER;
        *output << numberOfnetworkIP << FIELD_DELIMITER;
        std::set<int>::iterator networkIPsIt;
        for (networkIPsIt = networkIPs.begin(); networkIPsIt != networkIPs.end(); networkIPsIt++){
            *output << *networkIPsIt << FIELD_DELIMITER;
        }
        return true;
    }

    bool StartingInformation_Msg::ParseFromIstream(std::istream *input)
    {
        header.ParseFromIstream(input);
        return true;
    }

    void StartingInformation_Msg::FillHeader(const std::string senderIP)
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
        header.SetDataSize(calculateDataSize());
    }

    int StartingInformation_Msg::GetMasterIP() const
    {
        return masterIP;
    }

    void StartingInformation_Msg::SetMasterIP(int masterIP)
    {
        masterIP = masterIP;
    }
    unsigned int StartingInformation_Msg::GetNumberOfnetworkIP() const
    {
        return numberOfnetworkIP;
    }
/*
    void StartingInformation_Msg::SetNumberOfnetworkIP(unsigned int numberOfnetworkIP)
    {
        numberOfnetworkIP = numberOfnetworkIP;
    }
*/
    std::set<int> StartingInformation_Msg::GetNetworkIPs() const
    {
        return networkIPs;
    }

    void StartingInformation_Msg::SetNetworkIPs(std::set<int> networkIPs)
    {
        networkIPs = networkIPs;
        numberOfnetworkIP = networkIPs.size();
    }

    unsigned int StartingInformation_Msg::calculateDataSize() const{
        unsigned int size = 0;
        size += sizeof(masterIP);
        size += sizeof(numberOfnetworkIP);
        size += numberOfnetworkIP*sizeof(*(networkIPs.begin()));
        return size;
    }

}