#ifndef DISPATCHER_THREAD_H
#define DISPATCHER_THREAD_H
#pragma once

#include "logger/logger.hpp"

namespace DISPATCHER
{
	class Dispatcher_Thread
	{
	private:
		bool exit;
		LOGGER_T *log;

	public:
		Dispatcher_Thread();
		~Dispatcher_Thread();

		void Run();

		void SetExit(bool exit);
		bool GetExit() const;
	};
}
#endif