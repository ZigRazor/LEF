#ifndef DISPATCHER_THREAD_H
#define DISPATCHER_THREAD_H
#pragma once

namespace DISPATCHER
{
	class Dispatcher_Thread
	{
	private:
		bool exit;

	public:
		Dispatcher_Thread();
		~Dispatcher_Thread();

		void Run();

		void SetExit(bool exit);
		bool GetExit() const;
	};
}
#endif