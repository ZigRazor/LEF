#include "ConnectDisconnectMsg_Handler.hpp"
#include "shared/SharedData.hpp"

namespace HANDLER
{

    void ConnectDisconnectMsg_Handler::handleConnectToNetMsg(MESSAGES::ConnectToNet_Msg *message)
    {
        //Add IP to the network
        if (message)
        {
            SHARED::SharedData::AddElementToNetworkIPs(message->GetHeader().GetSenderIP());

            //clean
            delete message;
        }
    }
    void ConnectDisconnectMsg_Handler::handleDisconnectFromNetMsg(MESSAGES::DisconnectFromNet_Msg *message)
    {
        //Delete IP from the network
        if (message)
        {
            SHARED::SharedData::DeleteElementFromNetworkIPs(message->GetHeader().GetSenderIP());
            //clean
            delete message;
        }
    }

}