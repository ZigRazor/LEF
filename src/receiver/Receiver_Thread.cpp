#include "Receiver_Thread.hpp"
#include "shared/SharedData.hpp"
#include "msg/MessageFactory.hpp"
#include <unistd.h>

namespace RECEIVER
{
    Receiver_Thread::Receiver_Thread(std::string addr, unsigned int port, struct timeval tv)
    {
        exit = false;
        //Setup Customer
        std::cout << "Receiver Thread connetion IP " << addr << ":" << port  << std::endl;
        customer.init(addr,port);
        customer.connect();

        customer.setTimeoutOnReceive(tv);
    }

    Receiver_Thread::~Receiver_Thread()
    {
        customer.disconnect();
    }

    void Receiver_Thread::Run()
    {

        char* buffer = nullptr;
        while (!exit)
        {
            char* buffer = new char[MAXMSGSIZE];
            int bytesReceived = customer.receiveMessage(buffer,MAXMSGSIZE);
            if(bytesReceived > 0){ //Succesfully receive
                MESSAGES::BaseMessage* message = MESSAGES::MessageFactory::CreateMessage(buffer);
                if(message){
                    SHARED::SharedData::PushMessageQueue(message);
                    std::cout << "Enqueue message" << std::endl;
                }else{
                    //Discard Message (NOT VALID)
                    std::cerr << "Discard Message (NOT VALID)" << std::endl;
                }
            }else{
                //ERROR in receive to log
                std::cerr << "No message received" << std::endl;  
                usleep(1000000);                              
            }            
            delete buffer;
            buffer = nullptr;
        }
    }

    bool Receiver_Thread::GetExit() const
    {
        return exit;
    }

    void Receiver_Thread::SetExit(bool exit)
    {
        this->exit = exit;
    }
}