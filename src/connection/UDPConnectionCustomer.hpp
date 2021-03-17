#ifndef UDPCONNECTIONCUSTOMER_H
#define UDPCONNECTIONCUSTOMER_H
#pragma once

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "logger/logger.hpp"

#define MAXMSGSIZE 65000

namespace CONNECTION
{

  class UDPConnectionCustomer
  {
  private:
    int sockfd;
    struct sockaddr_in addr_info;
    bool isInitialized;
    bool isConnected;

    /**
   * @brief  Create Socket File Descriptor
   * @return 0 if all OK, -1 if something go wrong
   */
    int createSocketFileDescriptor();

    /**
   * @brief Fill Socket Information
   * @param port Port number
   * @param addr Internet address
   * @param family Socket Family (AF_INET | AF_INET6)
   * @return (void)
   */
    void fillSocketAddressInfo(unsigned int port, std::string addr, sa_family_t family);

    /**
   * @brief Bind Socket
   * @return 0 if all OK, -1 if something go wrong
   */
    int bindSocket();

    /**
   * @brief Receive a message from Socket
   * @param buffer The Buffer that will be filled with message
   * @param len The length of the buffer passed
   * @return  The number of Bytes received, or -1 if an error occurred. The return value will be 0 when the peer has performed an orderly shutdown.
   */
    int receive(char *buffer, size_t len) const;

    /**
   * @brief Receive a message from Socket
   * @param buffer The Buffer that will be filled with message
   * @param len The length of the buffer passed
   * @param receiveAddr The Address that sent the message received
   * @return The number of Bytes received, or -1 if an error occurred. The return value will be 0 when the peer has performed an orderly shutdown.
   */
    int receiveFrom(char *buffer, size_t len, sockaddr_in *receiveAddr) const;

    /**
   * @brief Send a message to Socket
   * @param buffer The Buffer that will be sent (message)
   * @param len The length of the buffer passed
   * @param sendAddr The Address that sent the message
   * @return On success, these calls return the number of characters sent. On error, -1 is returned, and errno is set appropriately.
   */
    int sendTo(const char *buffer,const size_t len, sockaddr_in *sendAddr);

    /**
   * @brief  Close the Socket
   * @return returns zero on success.  On error, -1 is returned, and errno is set appropriately.
   */
    int closeSocket();

  public:
    /**
   * @brief Create Customer
   */
    UDPConnectionCustomer();
    ~UDPConnectionCustomer();

    /**
    * @brief Initialize Customer
    * @param addr IP Address of the Socket ( if "ALL" is passed the INADDR_ANY is used)
    * @param port Port to connect the Socket
    * @param family Address Family (default = AF_INET)
    */
    int init(std::string addr, unsigned int port, sa_family_t family = AF_INET);
    /**
   * @brief Connect the Socket
   * @return 0 if all OK, -1 if something go wrong
   */
    int connect();

    /**
   * @brief Disconnect the Socket
   * @return 0 if all OK, -1 if something go wrong
   */
    int disconnect();

    int receiveMessage(char *buffer, size_t len) const;
    int sendMessage(const char *buffer,const size_t len, std::string addr, unsigned int port, sa_family_t family = AF_INET);
    void setTimeoutOnReceive(struct timeval tv);


  };
}
#endif