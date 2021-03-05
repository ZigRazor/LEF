#include "ConnectToNet_Msg.hpp"

namespace MESSAGES
{
    ConnectToNet_Msg::ConnectToNet_Msg()
    {
    }

    ConnectToNet_Msg::~ConnectToNet_Msg()
    {
    }

    bool ConnectToNet_Msg::SerializeToOstream(std::ostream* output) const
    {
        header.SerializeToOstream(output);
        return true;
    }

	bool ConnectToNet_Msg::ParseFromIstream(std::istream* input)
    {
        header.ParseFromIstream(input);
        return true;
    }

    void ConnectToNet_Msg::FillHeader(std::string senderIP)
    {
        header.SetCurrentTime();
        header.SetMessageId(MSG_ID);
        header.SetSenderIP_s(senderIP); //To Set Sender IP
        header.SetDataSize(0);
    }

}