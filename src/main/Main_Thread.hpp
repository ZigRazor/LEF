#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H
#pragma once

#include "logger/logger.hpp"

namespace MAIN
{
	class Main_Thread
	{
	private:
		bool exit;
		LOGGER_T *log;

	public:
		Main_Thread();
		~Main_Thread();

		void Run();

		void SetExit(bool exit);
		bool GetExit() const;
	};
}
#endif