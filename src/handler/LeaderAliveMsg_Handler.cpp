#include "LeaderAliveMsg_Handler.hpp"
#include "shared/SharedData.hpp"
#include "shared/ConfigData.hpp"
#include "logger/logger.hpp"

namespace HANDLER
{
    void LeaderAliveMsg_Handler::handlerLeaderAliveMsg(MESSAGES::LeaderAlive_Msg *message)
    {
        LOG(L_TRACE, "Handling LeaderAlive_Msg");
        //Handler Leader Alive Msg
        if (message)
        {
            std::set<int> networkIP = SHARED::SharedData::GetNetworkIPs();
            if (SHARED::SharedData::GetMasterIP() != -1 && networkIP.find(message->GetHeader().GetSenderIP()) == networkIP.end())
            {
                //ERROR No registered IP send a Leader Alive message
                LOG(L_ERROR, "No registered IP ( " << message->GetHeader().GetSenderIP_s() << " ) send a Leader Alive message");
            }
            else
            {
                if (SHARED::SharedData::GetMasterIP() == -1)
                { // No Master
                    //Set the first time the master IP
                    LOG(L_TRACE, "Set First Time Master IP");
                    SHARED::SharedData::SetMasterIP(message->GetHeader().GetSenderIP());
                    LOG(L_TRACE, "First Time Master IP set");
                }
                else
                { //Master Already Elected
                    if (SHARED::SharedData::GetMasterIP() != message->GetHeader().GetSenderIP())
                    {
                        //ERROR Leader Alive messagge Sent by no Elected Master
                        LOG(L_ERROR, "Leader Alive messagge Sent by no Elected Master ( " << message->GetHeader().GetSenderIP_s() << " )");
                    }
                    else
                    { //Peridic Leader Alive message received
                        LOG(L_TRACE, "Periodic Leader Alive Message Received");
                        if (!SHARED::SharedData::GetAmIMaster())
                        {
                            LOG(L_TRACE, "Set Master IP");
                            SHARED::SharedData::SetMasterIP(message->GetHeader().GetSenderIP());
                        }
                    }
                }
            }
            //clean
            delete message;
        }
        else
        {
            LOG(L_ERROR, "Invalid Pointer To Message");
        }
    }
}