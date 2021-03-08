#ifndef MAIN_THREAD_H
#define MAIN_THREAD_H
#pragma once
	
namespace MAIN{
class Main_Thread  
{
	private:
		bool exit;
	public:

		Main_Thread();
		~Main_Thread();

		void Run();

		void SetExit(bool exit);
		bool GetExit() const;

};
}
#endif