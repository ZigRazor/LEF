#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <future>
#include "receiver/Receiver_Thread.hpp"
#include "dispatcher/Dispatcher_Thread.hpp"
#include "channel/ChannelDefinition.hpp"
#include "sender/Sender_Thread.hpp"
#include "Main_Thread.hpp"
#include "shared/SharedData.hpp"

int main(int argc, char *argv[])
{
    // Check the number of parameters
    if (argc != 3)
    {
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " [ IP ]"
                  << " [ port ]" << std::endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return -1;
    }
    else
    {
        std::string ip(argv[1]);
        // Convert to ulong WITH CHECKING!
        char *pCh;
        unsigned int port = strtoul(argv[2], &pCh, 10);

        // Ensure argument was okay.
        if ((pCh == argv[2]) || (*pCh != '\0'))
        {
            std::cerr << "Invalid port number" << std::endl;
            return -1;
        }
        //DUMMY ///////
        SHARED::SharedData::SetAmIMaster(true);
        ///////////////

        //Initialize Channel
        CHANNEL::ChannelDefinition::addChannelToMap("ConnDisc_Channel", "127.0.0.1", 4002);
        CHANNEL::ChannelDefinition::addChannelToMap("Leader_Channel", "127.0.0.1", 4001);
        ////////////////////

        RECEIVER::Receiver_Thread *receiver_LeaderChannel;
        std::thread receiver_LeaderChannel_thread([&]() {
            struct timeval tv;
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            receiver_LeaderChannel = new RECEIVER::Receiver_Thread(CHANNEL::ChannelDefinition::getChannelByName("Leader_Channel")->GetIP(), CHANNEL::ChannelDefinition::getChannelByName("Leader_Channel")->GetPort(), tv);
            receiver_LeaderChannel->Run();
        });

        RECEIVER::Receiver_Thread *receiver_ConnDisc_Channel;
        std::thread receiver_ConnDisc_Channel_thread([&]() {
            struct timeval tv;
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            receiver_LeaderChannel = new RECEIVER::Receiver_Thread(CHANNEL::ChannelDefinition::getChannelByName("ConnDisc_Channel")->GetIP(), CHANNEL::ChannelDefinition::getChannelByName("ConnDisc_Channel")->GetPort(), tv);
            receiver_LeaderChannel->Run();
        });

        DISPATCHER::Dispatcher_Thread *dispatcher;
        std::thread dispatcher_thread([&]() {
            dispatcher = new DISPATCHER::Dispatcher_Thread();
            dispatcher->Run();
        });

        SENDER::Sender_Thread *sender;
        std::thread sender_thread([&]() {
            struct timeval tv;
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            sender = new SENDER::Sender_Thread(ip, port-1, tv);
            sender->Run();
        });

        MAIN::Main_Thread *main;
        std::thread main_thread([&]() {
            main = new MAIN::Main_Thread();
            main->Run();
        });

        //Exit Procedure
        std::string close_command = "";
        while (close_command != "close")
        {
            std::cout << "Type \"close\"  to quit execution " << std::endl;
            std::cin >> close_command;
        }

        dispatcher->SetExit(true);
        receiver_LeaderChannel->SetExit(true);
        receiver_ConnDisc_Channel->SetExit(true);
        sender->SetExit(true);
        main->SetExit(true);
        dispatcher_thread.join();
        receiver_LeaderChannel_thread.join();
        receiver_ConnDisc_Channel_thread.join();
        sender_thread.join();
        main_thread.join();

        //Clean All pointer
        if (receiver_LeaderChannel)
        {
            delete receiver_LeaderChannel;
        }

        if (receiver_ConnDisc_Channel)
        {
            delete receiver_ConnDisc_Channel;
        }

        if (dispatcher)
        {
            delete dispatcher;
        }

        if (sender)
        {
            delete sender;
        }

        if (main)
        {
            delete main;
        }
    }
    return 0;
}