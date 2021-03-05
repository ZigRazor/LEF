#include "MessageFactory.hpp"

#include "ConnectToNet_Msg.hpp"
#include "DisconnectFromNet_Msg.hpp"
#include "LeaderAlive_Msg.hpp"

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
            std::cout << "ConnectToNet_Msg Message" << std::endl;
            message = new ConnectToNet_Msg();
            std::istringstream input(buffer);
            message->ParseFromIstream(&input);
        }
        break;
        case DisconnectFromNet_Msg::MSG_ID:
        {
            std::cout << "DisconnectFromNet_Msg Message" << std::endl;
            message = new DisconnectFromNet_Msg();
            std::istringstream input(buffer);
            message->ParseFromIstream(&input);
        }
        break;
        case LeaderAlive_Msg::MSG_ID:
        {
            std::cout << "LeaderAlive_Msg Message" << std::endl;
            message = new LeaderAlive_Msg();
            std::istringstream input(buffer);
            message->ParseFromIstream(&input);
        }
        break;
        default:
            {
                //Unknown Message return nullptr
                std::cerr << "Unknown Message" << std::endl;
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