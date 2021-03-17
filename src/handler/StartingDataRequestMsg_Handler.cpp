#include "StartingDataRequestMsg_Handler.hpp"
#include "shared/SharedData.hpp"
#include "shared/ConfigData.hpp"
#include "msg/StartingInformation_Msg.hpp"

namespace HANDLER
{

    void StartingDataRequestMsg_Handler::handlerStartingInformationRequestMsg(MESSAGES::StartingInformationRequest_Msg *message)
    {
        if (message)
        {
            if (SHARED::SharedData::GetAmIMaster()) // Only if Master
            {

                //Send Starting Information

                MESSAGES::StartingInformation_Msg *siMsg = new MESSAGES::StartingInformation_Msg();
                siMsg->SetMasterIP(SHARED::SharedData::GetMasterIP());
                siMsg->SetNetworkIPs(SHARED::SharedData::GetNetworkIPs());
                siMsg->FillHeader(SHARED::ConfigData::IP);
                SHARED::SharedData::PushToSendQueue(siMsg);
                SHARED::SharedData::CVNotifyAll(SHARED::SharedData::GetToSendQueue_CV());

                //clean
                delete message;
            }
            else
            {
                //Discard Message
                std::cout << "Discarded Message Reason : I'M NOT MASTER" << std::endl;
            }
        }
    }
}