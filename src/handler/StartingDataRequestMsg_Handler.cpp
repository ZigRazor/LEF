#include "StartingDataRequestMsg_Handler.hpp"
#include "shared/SharedData.hpp"
#include "shared/ConfigData.hpp"
#include "msg/StartingInformation_Msg.hpp"
#include "logger/logger.hpp"

namespace HANDLER
{

    void StartingDataRequestMsg_Handler::handlerStartingInformationRequestMsg(MESSAGES::StartingInformationRequest_Msg *message)
    {
        if (message)
        {
            std::cout << SHARED::SharedData::GetAmIMaster() << std::endl;
            if (SHARED::SharedData::GetAmIMaster()) // Only if Master
            {

                //Send Starting Information
                LOG(L_DEBUG, "Sending Starting Information");
                MESSAGES::StartingInformation_Msg *siMsg = new MESSAGES::StartingInformation_Msg();
                siMsg->SetMasterIP(SHARED::SharedData::GetMasterIP());
                siMsg->SetNetworkIPs(SHARED::SharedData::GetNetworkIPs());
                siMsg->FillHeader(SHARED::ConfigData::IP);
                SHARED::SharedData::PushToSendQueue(siMsg);
                SHARED::SharedData::CVNotifyAll(SHARED::SharedData::GetToSendQueue_CV());
                
            }
            else
            {
                //Discard Message
                LOG(L_DEBUG, "Discarded Message Reason : I'M NOT MASTER");
            }
            //clean
            delete message;
        }
    }
}