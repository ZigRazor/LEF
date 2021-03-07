#include "Dispatcher_Thread.hpp"
#include "shared/SharedData.hpp"
#include "msg/ConnectToNet_Msg.hpp"
#include "msg/DisconnectFromNet_Msg.hpp"
#include "msg/LeaderAlive_Msg.hpp"
#include "handler/ConnectDisconnectMsg_Handler.hpp"
#include "handler/LeaderAliveMsg_Handler.hpp"

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
            if (!SHARED::SharedData::isMessageQueueEmpty())
            {
                MESSAGES::BaseMessage *message = SHARED::SharedData::PopMessageQueue();
                switch (message->GetHeader().GetMessageId())
                {
                case MESSAGES::ConnectToNet_Msg::MSG_ID:
                {
                    std::cout << "Handle ConnectToNet_Msg Message" << std::endl;
                    HANDLER::ConnectDisconnectMsg_Handler::handleConnectToNetMsg(dynamic_cast<MESSAGES::ConnectToNet_Msg *>(message));
                }
                break;
                case MESSAGES::DisconnectFromNet_Msg::MSG_ID:
                {
                    std::cout << "Handle DisconnectFromNet_Msg Message" << std::endl;
                    HANDLER::ConnectDisconnectMsg_Handler::handleDisconnectFromNetMsg(dynamic_cast<MESSAGES::DisconnectFromNet_Msg *>(message));
                }
                break;
                case MESSAGES::LeaderAlive_Msg::MSG_ID:
                {
                    std::cout << "Handle LeaderAlive_Msg Message" << std::endl;
                    HANDLER::LeaderAliveMsg_Handler::handlerLeaderAliveMsg(dynamic_cast<MESSAGES::LeaderAlive_Msg *>(message));
                }
                break;
                default:
                {
                    //Unknown Handler For message
                    std::cerr << "Unknown Handler with ID : " << message->GetHeader().GetMessageId() << std::endl;
                    if (message)
                    { // clean
                        delete message;
                    }
                }
                break;
                }
            }
            else
            {
                //wait
                usleep(100000);
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