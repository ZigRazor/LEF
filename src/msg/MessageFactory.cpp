#include "MessageFactory.hpp"

#include "ConnectToNet_Msg.hpp"
#include "DisconnectFromNet_Msg.hpp"
#include "LeaderAlive_Msg.hpp"
#include "msg/StartingInformationRequest_Msg.hpp"

namespace MESSAGES
{

    BaseMessage *MessageFactory::CreateMessage(char *buffer)
    {
        BaseMessage base_message(buffer);
        BaseMessage *message = nullptr;
        switch (base_message.GetHeader().GetMessageId())
        {
        case ConnectToNet_Msg::MSG_ID:
        {
            LOG( L_DEBUG, "ConnectToNet_Msg Message");
            message = new ConnectToNet_Msg();
            std::istringstream input(buffer);
            message->ParseFromIstream(&input);
        }
        break;
        case DisconnectFromNet_Msg::MSG_ID:
        {
            LOG( L_DEBUG, "DisconnectFromNet_Msg Message");
            message = new DisconnectFromNet_Msg();
            std::istringstream input(buffer);
            message->ParseFromIstream(&input);
        }
        break;
        case LeaderAlive_Msg::MSG_ID:
        {
            LOG( L_DEBUG, "LeaderAlive_Msg Message");
            message = new LeaderAlive_Msg();
            std::istringstream input(buffer);
            message->ParseFromIstream(&input);
        }
        break;
        case StartingInformationRequest_Msg::MSG_ID:
        {
            LOG( L_DEBUG, "StartingInformationRequest_Msg Message");
            message = new StartingInformationRequest_Msg();
            std::istringstream input(buffer);
            message->ParseFromIstream(&input);
        }
        break;
        default:
        {
            //Unknown Message return nullptr
            LOG( L_ERROR, "Unknown Message");
        }
        break;
        }

        return message;
    }

    void MessageFactory::DeleteMessage(BaseMessage *message)
    {
        if (message)
        {
            delete message;
        }
    }
}