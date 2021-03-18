#include "Sender_Thread.hpp"
#include "shared/SharedData.hpp"
#include <unistd.h>

namespace SENDER
{
    Sender_Thread::Sender_Thread(std::string addr, unsigned int port, struct timeval tv)
    {
        exit = false;
        
        //Setup Customer
        LOG( L_DEBUG, "Sender Thread connetion IP " << addr << ":" << port);
        if (customer.init(addr, port) == 0)
        {
            if (customer.connect() == 0)
            {
                customer.setTimeoutOnReceive(tv);
            }
            else
            {
                //ERROR
                LOG( L_ERROR, "Error in Connect Socket");
                exit = true;
            }
        }
        else
        {
            //ERROR
            LOG( L_ERROR, "Error in Init Socket");
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
            }
            else
            {
                // message are present in queue
                MESSAGES::BaseMessage *message = SHARED::SharedData::PopToSendQueue();
                std::ostringstream output;
                message->SerializeToOstream(&output);
                LOG( L_DEBUG, message->GetHeader().GetReceiverIP_s());
                int byte_sent = customer.sendMessage(output.str().c_str(), output.str().size(), message->GetHeader().GetReceiverIP_s(), message->GetHeader().GetReceiverPort());
                LOG( L_DEBUG, "Message Sent of " << byte_sent << " Bytes");
                //clean
                if (message)
                {
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