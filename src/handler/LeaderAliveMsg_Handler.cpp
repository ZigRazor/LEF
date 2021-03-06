#include "LeaderAliveMsg_Handler.hpp"

namespace HANDLER
{
    void LeaderAliveMsg_Handler::handlerLeaderAliveMsg(MESSAGES::LeaderAlive_Msg *message)
    {
        //Handler Leader Alive Msg
        if (message)
        {
            //clean
            delete message;
        }
    }
}