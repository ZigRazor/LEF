#include "Main_Thread.hpp"
#include "shared/SharedData.hpp"
#include "shared/ConfigData.hpp"
#include "msg/LeaderAlive_Msg.hpp"
#include "msg/ConnectToNet_Msg.hpp"
#include "msg/DisconnectFromNet_Msg.hpp"
#include "msg/StartingInformationRequest_Msg.hpp"
#include <unistd.h>
#include <thread>

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
        //Connect to the network
        MESSAGES::ConnectToNet_Msg *connectMsg = new MESSAGES::ConnectToNet_Msg();
        connectMsg->FillHeader(SHARED::ConfigData::IP);
        SHARED::SharedData::PushToSendQueue(connectMsg);
        SHARED::SharedData::CVNotifyAll(SHARED::SharedData::GetToSendQueue_CV());

        //Request Starting Data
        MESSAGES::StartingInformationRequest_Msg *startingInfoMsg = new MESSAGES::StartingInformationRequest_Msg();
        startingInfoMsg->FillHeader(SHARED::ConfigData::IP);
        SHARED::SharedData::PushToSendQueue(startingInfoMsg);
        SHARED::SharedData::CVNotifyAll(SHARED::SharedData::GetToSendQueue_CV());

        // Wait Starting Data
        if (SHARED::SharedData::GetMasterIP() == -1)
        {
            LOG( L_DEBUG, "Waiting Starting Data");
            if (!SHARED::SharedData::CVWaitFor(SHARED::SharedData::GetStartingDataUpdated_CV(), SHARED::SharedData::GetStartingDataUpdated_Mutex(), 10000))
            { //timeout elapsed No MASTER
                LOG( L_DEBUG, "timeout elapsed No MASTER");
                int ip = 0;
                inet_pton(AF_INET, SHARED::ConfigData::IP.c_str(), &(ip));
                SHARED::SharedData::SetMasterIP(ip);
                SHARED::SharedData::SetAmIMaster(true);
                SHARED::SharedData::AddElementToNetworkIPs(ip);
            }
        }
        // Starting Data Set or I'm the only in the network
        LOG( L_DEBUG, "Starting Data Set or I'm the only in the network");
        char *buffer = nullptr;
        std::thread leaderAliveSender_t([&]() {
            while (true)
            {
                if (SHARED::SharedData::GetAmIMaster())
                {
                    // I AM MASTER
                    MESSAGES::LeaderAlive_Msg *laMsg = new MESSAGES::LeaderAlive_Msg();
                    laMsg->FillHeader(SHARED::ConfigData::IP);
                    SHARED::SharedData::PushToSendQueue(laMsg);
                    SHARED::SharedData::CVNotifyAll(SHARED::SharedData::GetToSendQueue_CV());
                    sleep(1);
                }
                else
                {
                    sleep(1);
                }
            }
        });
        while (!exit)
        {
            //DOING SOMETHING
            sleep(1);
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