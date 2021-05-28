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
                socket->setsockopt(ZMQ_SUBSCRIBE, channel.GetChannelName().c_str(), 0);
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
        default:
            LOG(L_ERROR, " No Communication Type");
            break;
        }
        connectionString << channel.GetIP();
        connectionString << ":";
        connectionString << channel.GetPort();
        
        socket_ptr->connect(connectionString.str());
    }
}