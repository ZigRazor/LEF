#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H
#pragma once
#include <sstream>
#include "connection/ConnectionCustomer.hpp"
#include "channel/Channel.hpp"
#include "logger/logger.hpp"

namespace RECEIVER
{

	class Receiver_Thread
	{
	private:
		CONNECTION::ConnectionCustomer customer;
		bool exit;
		std::string address;
		unsigned int portNumber;
		
	public:
		Receiver_Thread(const CHANNEL::Channel &channel, struct timeval tv = {1, 0});
		~Receiver_Thread();
		void Run();

		void SetExit(bool exit);
		bool GetExit() const;
	};
}
#endif