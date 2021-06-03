#include "ConnectionCustomer.hpp"
#include <sstream>

namespace CONNECTION
{
    ConnectionCustomer::ConnectionCustomer()
    {
        // initialize the zmq context with a single IO thread
        //context{1};
    }

    ConnectionCustomer::~ConnectionCustomer()
    {
    }

    int ConnectionCustomer::connect(const CHANNEL::Channel &channel, const E_ConnectionMode &connectionMode)
    {
        LOG(L_DEBUG, " Connection");
        zmq::socket_t *socket;
        if (connectionMode == E_ConnectionMode::SEND)
        {
            if (sendSocket.find(channel.GetChannelName()) == sendSocket.end())
            {
                socket = new zmq::socket_t(context, zmq::socket_type::xpub);
                socketConnection(socket, channel);
                sendSocket[channel.GetChannelName()] = socket;
            }
            else
            {
                LOG(L_ERROR, " Channel Already Open in SEND MODE");
            }
        }
        else if (connectionMode == E_ConnectionMode::RECEIVE)
        {
            if (recvSocket.find(channel.GetChannelName()) == recvSocket.end())
            {
                socket = new zmq::socket_t(context, zmq::socket_type::xsub);
                //socket->setsockopt(ZMQ_SUBSCRIBE, channel.GetChannelName().c_str(), 0);
                socketConnection(socket, channel);
                recvSocket[channel.GetChannelName()] = socket;
            }
            else
            {
                LOG(L_ERROR, " Channel Already Open in RECEIVE MODE");
            }
        }
        else if (connectionMode == E_ConnectionMode::SEND_RECEIVE)
        {
            if (sendSocket.find(channel.GetChannelName()) == sendSocket.end())
            {
                socket = new zmq::socket_t(context, zmq::socket_type::xpub);
                socketConnection(socket, channel);
                sendSocket[channel.GetChannelName()] = socket;
            }
            else
            {
                LOG(L_ERROR, " Channel Already Open in SEND MODE");
            }
            if (recvSocket.find(channel.GetChannelName()) == recvSocket.end())
            {
                socket = new zmq::socket_t(context, zmq::socket_type::xsub);
                socket->setsockopt(ZMQ_SUBSCRIBE, channel.GetChannelName().c_str(), 0);
                socketConnection(socket, channel);
                recvSocket[channel.GetChannelName()] = socket;
                zmq::pollitem_t pollinItem;
                pollinItem.socket = socket;
                pollinItem.events = ZMQ_POLLIN;
                pollingItems.push_back(pollinItem);
            }
            else
            {
                LOG(L_ERROR, " Channel Already Open in RECEIVE MODE");
            }
        }
        else
        {
            LOG(L_ERROR, "Not Valid Connectio Mode");
            return 1;
        }

        return 0;
    }

    int ConnectionCustomer::disconnect(){
        std::map<std::string, zmq::socket_t *>::iterator sendSocketIt;
		std::map<std::string, zmq::socket_t *>::iterator recvSocketIt;
        for( sendSocketIt = sendSocket.begin(); sendSocketIt != sendSocket.end(); ++sendSocketIt){
            sendSocketIt->second->close();
        }
        for( recvSocketIt = recvSocket.begin(); recvSocketIt != recvSocket.end(); ++recvSocketIt){
            recvSocketIt->second->close();
        }
    }

    void ConnectionCustomer::socketConnection(zmq::socket_t *socket_ptr, const CHANNEL::Channel &channel)
    {
        std::stringstream connectionString;
        switch (channel.GetCommunicationType())
        {
        case CHANNEL::Channel::E_CommunicationType::INPROC:
            connectionString << "inproc://";
            break;
        case CHANNEL::Channel::E_CommunicationType::TCP:
            connectionString << "tcp://";
            break;
        case CHANNEL::Channel::E_CommunicationType::UDP:
            connectionString << "udp://";
            break;
        case CHANNEL::Channel::E_CommunicationType::EPGM:
            connectionString << "epgm://";
            break;
        case CHANNEL::Channel::E_CommunicationType::PGM:
            connectionString << "pgm://";
            break;
        default:
            LOG(L_ERROR, " No Communication Type");
            break;
        }
        connectionString << channel.GetIP();
        connectionString << ":";
        connectionString << channel.GetPort();

        socket_ptr->connect(connectionString.str().c_str());
    }

    int ConnectionCustomer::receiveMessage(char *buffer, size_t len) const
    {
        if (zmq::poll(pollingItems) > 0)
        {
            for (auto pollIt = pollingItems.begin(); pollIt != pollingItems.end(); ++pollIt)
            {
                if (pollIt->revents > 0)
                {
                    /* Create an empty ØMQ message */
                    zmq_msg_t msg;
                    int rc = zmq_msg_init(&msg);
                    if (rc == 0)
                    {
                        /* Block until a message is available to be received from socket */
                        rc = zmq_recv(pollIt->socket, &msg, 0, 0);
                        if (rc == 0)
                        {
                            int messageLen = zmq_msg_size(&msg);
                            if (messageLen > len)
                            {
                                //ERROR MESSAGE TOO LONG
                                return -1;
                            }
                            std::memcpy(buffer, zmq_msg_data(&msg), messageLen);
                            /* Release message */
                            zmq_msg_close(&msg);
                            return messageLen;
                        }
                    }
                }
            }
        }
        //ERROR
        return -1;
    }
    int ConnectionCustomer::sendMessage(const char *buffer, const size_t len, const CHANNEL::Channel &channel)
    {
        std::map<std::string, zmq::socket_t *>::iterator socketIt = sendSocket.find(channel.GetChannelName());
        if (socketIt != sendSocket.end())
        {

            /* Create a new message, allocating 6 bytes for message content */
            zmq_msg_t msg;
            int rc = zmq_msg_init_size(&msg, len);
            if (rc == 0)
            {
                /* Fill in message content with buffer */
                memcpy(zmq_msg_data(&msg), buffer, len);
                /* Send the message to the socket */
                rc = zmq_msg_send(&msg, socketIt->second, 0);
                if(rc == len){
                    //ALL BYTES SENT
                    return len;
                }else{
                    //NOT ALL BYTES SENT
                    return rc;
                }
            }
        }
        else
        {
            //ERROR
            return -1;
        }
        //ERROR
        return -1;
    }
}