#include "Main_Thread.hpp"
#include "shared/SharedData.hpp"
#include "msg/LeaderAlive_Msg.hpp"
#include <unistd.h>


namespace MAIN
{

    Main_Thread::Main_Thread()
    {
        exit = false;
    }

    Main_Thread::~Main_Thread()
    {
    }

    void Main_Thread::Run()
    {

        char *buffer = nullptr;
        while (!exit)
        {
            if (SHARED::SharedData::GetAmIMaster())
            {
                // I AM MASTER
                MESSAGES::LeaderAlive_Msg*  laMsg = new MESSAGES::LeaderAlive_Msg();
                laMsg->FillHeader("127.0.0.1");
                SHARED::SharedData::PushToSendQueue(laMsg);
                SHARED::SharedData::CVNotifyAll(SHARED::SharedData::GetToSendQueue_CV());
                sleep(1);                
            }else{
                sleep(1);
            }
        }
    }

    bool Main_Thread::GetExit() const
    {
        return exit;
    }

    void Main_Thread::SetExit(bool exit)
    {
        this->exit = exit;
    }
}