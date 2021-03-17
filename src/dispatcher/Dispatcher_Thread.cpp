#include "Dispatcher_Thread.hpp"
#include "shared/SharedData.hpp"
#include "msg/ConnectToNet_Msg.hpp"
#include "msg/DisconnectFromNet_Msg.hpp"
#include "msg/LeaderAlive_Msg.hpp"
#include "msg/StartingInformationRequest_Msg.hpp"
#include "handler/ConnectDisconnectMsg_Handler.hpp"
#include "handler/LeaderAliveMsg_Handler.hpp"
#include "handler/StartingDataRequestMsg_Handler.hpp"

#include <unistd.h>

namespace DISPATCHER
{
    Dispatcher_Thread::Dispatcher_Thread()
    {
    }

    Dispatcher_Thread::~Dispatcher_Thread()
    {
    }

    void Dispatcher_Thread::Run()
    {

        char *buffer = nullptr;
        while (!exit)
        {
            if (SHARED::SharedData::isMessageQueueEmpty())
            {
                SHARED::SharedData::CVWait(SHARED::SharedData::GetMessageQueue_CV(), SHARED::SharedData::GetMessageQueue_Mutex());
            }
            else
            { // message are present in queue
                MESSAGES::BaseMessage *message = SHARED::SharedData::PopMessageQueue();
                switch (message->GetHeader().GetMessageId())
                {
                case MESSAGES::ConnectToNet_Msg::MSG_ID:
                {
                    LOG( L_DEBUG, "Handle ConnectToNet_Msg Message");
                    HANDLER::ConnectDisconnectMsg_Handler::handleConnectToNetMsg(dynamic_cast<MESSAGES::ConnectToNet_Msg *>(message));
                }
                break;
                case MESSAGES::DisconnectFromNet_Msg::MSG_ID:
                {
                    LOG( L_DEBUG, "Handle DisconnectFromNet_Msg Message");
                    HANDLER::ConnectDisconnectMsg_Handler::handleDisconnectFromNetMsg(dynamic_cast<MESSAGES::DisconnectFromNet_Msg *>(message));
                }
                break;
                case MESSAGES::LeaderAlive_Msg::MSG_ID:
                {
                    LOG( L_DEBUG, "Handle LeaderAlive_Msg Message");
                    HANDLER::LeaderAliveMsg_Handler::handlerLeaderAliveMsg(dynamic_cast<MESSAGES::LeaderAlive_Msg *>(message));
                }
                break;
                case MESSAGES::StartingInformationRequest_Msg::MSG_ID:
                {
                    LOG( L_DEBUG, "Handle StartingInformationRequest_Msg Message");
                    HANDLER::StartingDataRequestMsg_Handler::handlerStartingInformationRequestMsg(dynamic_cast<MESSAGES::StartingInformationRequest_Msg *>(message));
                }
                break;
                default:
                {
                    //Unknown Handler For message
                    LOG( L_ERROR, "Unknown Handler with ID : " << message->GetHeader().GetMessageId());
                    if (message)
                    { // clean
                        delete message;
                    }
                }
                break;
                }
            }
        }
    }

    bool Dispatcher_Thread::GetExit() const
    {
        return exit;
    }

    void Dispatcher_Thread::SetExit(bool exit)
    {
        this->exit = exit;
    }

}