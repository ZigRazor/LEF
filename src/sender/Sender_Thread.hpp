#ifndef SENDER_THREAD_H
#define SENDER_THREAD_H
#pragma once
#include "logger/logger.hpp"
#include "connection/ConnectionCustomer.hpp"
#include "channel/Channel.hpp"
#include "channel/ChannelDefinition.hpp"

namespace SENDER
{
	class Sender_Thread
	{
	private:
		CONNECTION::ConnectionCustomer customer;
		bool exit;
		LOGGER_T *log;

	public:
		Sender_Thread(const CHANNEL::Channel &channel, struct timeval tv = {1, 0});
		~Sender_Thread();

		void Run();

		void SetExit(bool exit);
		bool GetExit() const;
	};
}
#endif