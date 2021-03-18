#include "UDPConnectionCustomer.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

namespace CONNECTION
{

    UDPConnectionCustomer::UDPConnectionCustomer()
    {
        sockfd = 0;
        isInitialized = false;
        isConnected = false;
    }

    UDPConnectionCustomer::~UDPConnectionCustomer()
    {
        closeSocket();
    }

    int UDPConnectionCustomer::createSocketFileDescriptor()
    {
        // Creating socket file descriptor
        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            //ERROR
            return -1;
        }

        return 0;
    }

    void UDPConnectionCustomer::fillSocketAddressInfo(unsigned int port, std::string addr, sa_family_t family)
    {
        addr_info.sin_port = htons(port);
        if (addr == "ALL")
        {
            addr_info.sin_addr.s_addr = INADDR_ANY;
        }
        else
        {
            addr_info.sin_addr.s_addr = INADDR_ANY; //inet_addr(addr.c_str());
        }
        addr_info.sin_family = family;
    }

    int UDPConnectionCustomer::bindSocket()
    {
        // Bind the socket with the server address
        if (bind(sockfd, (const struct sockaddr *)&addr_info,
                 sizeof(addr_info)) < 0)
        {
            //ERROR
            return -1;
        }
        return 0;
    }

    int UDPConnectionCustomer::receive(char *buffer, size_t len) const
    {
        if (isInitialized && isConnected)
        {
            return recv(sockfd, buffer, len, 0);
        }
        else
        {
            //error
            LOG( L_ERROR, "Customer Not Initialized or Connected");
            return 0;
        }
    }

    int UDPConnectionCustomer::receiveFrom(char *buffer, size_t len, sockaddr_in *receiveAddr) const
    {
        if (isInitialized && isConnected)
        {
            unsigned int receiveAddrLen = sizeof(*receiveAddr);
            return recvfrom(sockfd, buffer, len, 0, (struct sockaddr *)receiveAddr, &receiveAddrLen);
        }
        else
        {
            //error
            LOG( L_ERROR, "Customer Not Initialized or Connected");
            return 0;
        }
    }

    int UDPConnectionCustomer::sendTo(const char *buffer, const size_t len, sockaddr_in *sendAddr)
    {
        if (isInitialized && isConnected)
        {
            unsigned int sendAddrLen = sizeof(*sendAddr);
            return sendto(sockfd, buffer, len, MSG_CONFIRM, (const struct sockaddr *)sendAddr, sendAddrLen);
        }
        else
        {
            //error
            LOG( L_ERROR, "Customer Not Initialized or Connected");
            return 0;
        }
    }

    int UDPConnectionCustomer::closeSocket()
    {
        isInitialized = false;
        isConnected = false;
        return close(sockfd);
    }

    int UDPConnectionCustomer::init(std::string addr, unsigned int port, sa_family_t family)
    {
        fillSocketAddressInfo(port, addr, family);
        int result = createSocketFileDescriptor();
        if (result >= 0)
        {
            LOG( L_DEBUG, "Socket Initialized");
            isInitialized = true;
        }
        int broadcastEnable = 1;
        int ret = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
        if (ret < 0)
        {

            LOG( L_ERROR, "Error in setting Broadcast option");

            close(sockfd);

            return ret;
        }

        int optval = 1;
        ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
        if (ret < 0)
        {

            LOG( L_ERROR, "Error in setting Reuse Port option");

            close(sockfd);

            return ret;
        }

        struct ip_mreq m;
        m.imr_interface.s_addr = addr_info.sin_addr.s_addr;
        m.imr_multiaddr.s_addr = inet_addr("224.0.0.150");
        ret = setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&m, sizeof(m));

        if (ret < 0)
        {

            LOG( L_ERROR, "Error in setting Multicast group option");

            close(sockfd);

            return ret;
        }

        int loop = 1;
        ret = setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
        if (ret < 0)
        {

            LOG( L_ERROR, "Error in setting Multicast Loop option");

            close(sockfd);

            return ret;
        }
        return result;
    }

    int UDPConnectionCustomer::connect()
    {
        int result = bindSocket();
        if (result >= 0)
        {
            LOG( L_DEBUG, "Socket Connected");
            isConnected = true;
        }
        else
        {
            LOG( L_ERROR, "Failed to bind socket! " << strerror(errno));
        }
        return result;
    }

    int UDPConnectionCustomer::disconnect()
    {
        return closeSocket();
    }

    int UDPConnectionCustomer::receiveMessage(char *buffer, size_t len) const
    {
        return receive(buffer, len);
    }

    int UDPConnectionCustomer::sendMessage(const char *buffer, const size_t len, std::string addr, unsigned int port, sa_family_t family)
    {
        struct sockaddr_in sendAddr;
        sendAddr.sin_port = htons(port);
        sendAddr.sin_addr.s_addr = inet_addr(addr.c_str());
        sendAddr.sin_family = family;
        return sendTo(buffer, len, &sendAddr);
    }

    void UDPConnectionCustomer::setTimeoutOnReceive(struct timeval tv)
    {
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv);
    }

}