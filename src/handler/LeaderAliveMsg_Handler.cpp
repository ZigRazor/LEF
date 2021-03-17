#include "LeaderAliveMsg_Handler.hpp"
#include "shared/SharedData.hpp"
#include "shared/ConfigData.hpp"

namespace HANDLER
{
    void LeaderAliveMsg_Handler::handlerLeaderAliveMsg(MESSAGES::LeaderAlive_Msg *message)
    {
        //Handler Leader Alive Msg
        if (message)
        {
            std::set<int> networkIP = SHARED::SharedData::GetNetworkIPs();
            if(  SHARED::SharedData::GetMasterIP() != -1 &&  networkIP.find( message->GetHeader().GetSenderIP()) == networkIP.end() ){
                //ERROR No registered IP send a Leader Alive message
                std::cerr << "No registered IP ( " << message->GetHeader().GetSenderIP_s() <<" ) send a Leader Alive message" << std::endl;
            }else{
                if(SHARED::SharedData::GetMasterIP() == -1){ // No Master
                    //Set the first time the master IP
                    SHARED::SharedData::SetMasterIP(message->GetHeader().GetSenderIP());                     
                }else{ //Master Already Elected
                    if(SHARED::SharedData::GetMasterIP() != message->GetHeader().GetSenderIP()){
                        //ERROR Leader Alive messagge Sent by no Elected Master
                        std::cerr << "Leader Alive messagge Sent by no Elected Master ( " << message->GetHeader().GetSenderIP_s() <<" )"<< std::endl;
                    }else{ //Peridic Leader Alive message received
                        if(!SHARED::SharedData::GetAmIMaster()){
                            SHARED::SharedData::SetMasterIP(message->GetHeader().GetSenderIP());
                        }
                    }
                }
            }
            //clean
            delete message;
        }
    }
}