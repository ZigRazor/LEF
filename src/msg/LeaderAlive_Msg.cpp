#include "LeaderAlive_Msg.hpp"

namespace MESSAGES
{
    LeaderAlive_Msg::LeaderAlive_Msg()
    {
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
        header.SetDataSize(0);
    }

}