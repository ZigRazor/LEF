#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H
#pragma once

#include "connection/UDPConnectionCustomer.hpp"

namespace SENDER
{
	class Sender_Thread
	{
	private:
		CONNECTION::UDPConnectionCustomer customer;
		bool exit;

	public:
		Sender_Thread(std::string addr, unsigned int port, struct timeval tv = {1, 0});
		~Sender_Thread();

		void Run();

		void SetExit(bool exit);
		bool GetExit() const;
	};
}
#endif