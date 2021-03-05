#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <future>
#include "receiver/Receiver_Thread.hpp"
#include "dispatcher/Dispatcher_Thread.hpp"

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
        
        RECEIVER::Receiver_Thread* receiver;
        std::thread receiver_thread ([&]() {
            struct timeval tv;
            tv.tv_sec = 10;
            tv.tv_usec = 0;
                receiver = new RECEIVER::Receiver_Thread(ip,port,tv);
                receiver->Run();
            });

        DISPATCHER::Dispatcher_Thread* dispatcher;
        std::thread dispatcher_thread ([&]() {
                dispatcher = new DISPATCHER::Dispatcher_Thread();
                dispatcher->Run();
            });
        
        //Exit Procedure
        std::string close_command = "";
        while (close_command != "close"){
            std::cout << "Type \"close\"  to quit execution " << std::endl;
            std::cin >> close_command;
        }

        dispatcher->SetExit(true);
        receiver->SetExit(true);
        dispatcher_thread.join();
        receiver_thread.join();
   
    }
    return 0;
}