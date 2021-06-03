#ifndef CONNECTIONCUSTOMER_H
#define CONNECTIONCUSTOMER_H
#pragma once

#include <string>
#include <zmq.hpp>
#include "logger/logger.hpp"
#include "channel/Channel.hpp"
#include <map>

#define MAXMSGSIZE 65000

namespace CONNECTION
{
	class ConnectionCustomer
	{

	public:
		typedef enum ConnectionMode_Enumeration
		{
			SEND,
			RECEIVE,
			SEND_RECEIVE
		} E_ConnectionMode;

		ConnectionCustomer();
		~ConnectionCustomer();

		/**
   		  * @brief Connect the Socket
   		  * @return 0 if all OK, -1 if something go wrong
   			*/
		int connect(const CHANNEL::Channel &channel, const E_ConnectionMode &connectionMode);

		/**
   			* @brief Disconnect the Socket
   			* @return 0 if all OK, -1 if something go wrong
   		*/
		int disconnect();

		int receiveMessage(char *buffer, size_t len) const;
		int sendMessage(const char *buffer, const size_t len, const CHANNEL::Channel &channel);

	private:
		void socketConnection(zmq::socket_t *socket_ptr, const CHANNEL::Channel &channel);

		zmq::context_t context{1};
		std::map<std::string, zmq::socket_t *> sendSocket;
		std::map<std::string, zmq::socket_t *> recvSocket;
		std::vector<zmq::pollitem_t> pollingItems;
	};
}
#endif