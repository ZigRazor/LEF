#include "DisconnectFromNet_Msg.hpp"

namespace MESSAGES
{
    DisconnectFromNet_Msg::DisconnectFromNet_Msg()
    {
    }

    DisconnectFromNet_Msg::~DisconnectFromNet_Msg()
    {
    }

    bool DisconnectFromNet_Msg::SerializeToOstream(std::ostream* output) const
    {
        header.SerializeToOstream(output);
        return true;
    }

	bool DisconnectFromNet_Msg::ParseFromIstream(std::istream* input)
    {
        header.ParseFromIstream(input);
        return true;
    }

    void DisconnectFromNet_Msg::FillHeader(std::string senderIP)
    {
        header.SetCurrentTime();
        header.SetMessageId(MSG_ID);
        header.SetSenderIP_s(senderIP); //To Set Sender IP
        header.SetDataSize(0);
    }

}