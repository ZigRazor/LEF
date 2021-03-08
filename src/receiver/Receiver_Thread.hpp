#ifndef RECEIVER_THREAD_H
#define RECEIVER_THREAD_H
#pragma once
#include "connection/UDPConnectionCustomer.hpp"

namespace RECEIVER
{

	class Receiver_Thread
	{
	private:
		CONNECTION::UDPConnectionCustomer customer;
		bool exit;
		std::string address;
		unsigned int portNumber;

	public:
		Receiver_Thread(std::string addr, unsigned int port, struct timeval tv = {1,0});
		~Receiver_Thread();
		void Run();

		void SetExit(bool exit);
		bool GetExit() const;
	};
}
#endif