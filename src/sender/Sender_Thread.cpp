#include "Sender_Thread.hpp"
#include "shared/SharedData.hpp"
#include <unistd.h>

namespace SENDER
{
    Sender_Thread::Sender_Thread(std::string addr, unsigned int port, struct timeval tv)
    {
        exit = false;
        //Setup Customer
        std::cout << "Sender Thread connetion IP " << addr << ":" << port << std::endl;
        if(customer.init(addr, port) == 0){
            if (customer.connect() == 0){
                customer.setTimeoutOnReceive(tv);
            }else{
                //ERROR
                std::cerr << "Error in Connect Socket" << std::endl;
                exit = true;
            }
        }else{
            //ERROR
            std::cerr << "Error in Init Socket" << std::endl;
            exit = true;
        }

        
    }

    Sender_Thread::~Sender_Thread()
    {
        customer.disconnect();
    }

    void Sender_Thread::Run()
    {

        char *buffer = nullptr;
        while (!exit)
        {
            if (SHARED::SharedData::isToSendQueueEmpty())
            {
                SHARED::SharedData::CVWait(SHARED::SharedData::GetToSendQueue_CV(), SHARED::SharedData::GetToSendQueue_Mutex());
            }else{
                // message are present in queue
                MESSAGES::BaseMessage *message = SHARED::SharedData::PopToSendQueue();
                std::ostringstream  output;
                message->SerializeToOstream(&output);
                std::cout << message->GetHeader().GetReceiverIP_s() << std::endl;
                int byte_sent = customer.sendMessage(output.str().c_str(),output.str().size(),message->GetHeader().GetReceiverIP_s(),message->GetHeader().GetReceiverPort());
                std::cout << "Message Sent of " << byte_sent << " Bytes" << std::endl;
                //clean
                if(message){
                    delete message;
                }
            }
        }
    }

    bool Sender_Thread::GetExit() const
    {
        return exit;
    }

    void Sender_Thread::SetExit(bool exit)
    {
        this->exit = exit;
    }

}