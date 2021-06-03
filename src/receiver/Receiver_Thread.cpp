#include "Receiver_Thread.hpp"
#include "shared/SharedData.hpp"
#include "msg/MessageFactory.hpp"

namespace RECEIVER
{
    Receiver_Thread::Receiver_Thread(const CHANNEL::Channel &channel, struct timeval tv)
    {
        //Setup Customer
        LOG( L_DEBUG, "Receiver Thread connetion IP " << channel.GetIP() << ":" << channel.GetPort());
        this->address = channel.GetIP();
        this->portNumber = channel.GetPort();
        int result = 0;
        result = customer.connect(channel,CONNECTION::ConnectionCustomer::E_ConnectionMode::RECEIVE);
        
        //customer.setTimeoutOnReceive(tv);
    }

    Receiver_Thread::~Receiver_Thread()
    {
        customer.disconnect();
        CLOSE_LOGGER();
    }

    void Receiver_Thread::Run()
    {

        char *buffer = nullptr;
        while (!exit)
        {
            char *buffer = new char[MAXMSGSIZE];
            int bytesReceived = customer.receiveMessage(buffer, MAXMSGSIZE);
            if (bytesReceived > 0)
            { //Succesfully receive
                MESSAGES::BaseMessage *message = MESSAGES::MessageFactory::CreateMessage(buffer);
                if (message)
                {
                    if (message->GetHeader().GetReceiverIP_s() != address || message->GetHeader().GetReceiverPort() != portNumber)
                    {
                        LOG( L_ERROR, "Intecepted Wrong Message");
                    }
                    else
                    {
                        SHARED::SharedData::PushMessageQueue(message);
                        SHARED::SharedData::CVNotifyAll(SHARED::SharedData::GetMessageQueue_CV());
                        LOG( L_DEBUG, "Enqueue message");
                    }
                }
                else
                {
                    //Discard Message (NOT VALID)
                    LOG( L_ERROR, "Discard Message (NOT VALID)");
                }
            }
            else
            {
                //ERROR in receive to log
                LOG( L_ERROR, "No message received reason: " << bytesReceived);
                usleep(1000000);
            }
            delete[] buffer;
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