#ifndef SHAREDDATA_H
#define SHAREDDATA_H
#pragma once

#include <mutex>
#include <set>
#include <queue>
#include "msg/BaseMessage.hpp"

namespace SHARED
{

	class SharedData
	{
	private:
		static bool amIMaster;
		static int masterIP;
		static std::set<int> networkIPs;

		//Queue
		static std::queue<MESSAGES::BaseMessage*> messageQueue;

		// Mutex
		static std::mutex m_amIMaster;
		static std::mutex m_masterIP;
		static std::mutex m_networkIPs;
		static std::mutex m_messageQueue;

	public:
		SharedData() = delete;
		~SharedData() = delete;

		static int GetMasterIP();
		static void SetMasterIP(int _masterIP);
		static bool GetAmIMaster();
		static void SetAmIMaster(bool _amIMaster);
		static std::set<int> GetNetworkIPs();
		static std::set<int> &GetNetworkIPs_Ref(); //this operation should be externally muted
		static void SetNetworkIPs(std::set<int> networkIPs);
		static void AddElementToNetworkIPs(int networkIP);
		static void DeleteElementFromNetworkIPs(int networkIP);

		// Queue Operation
		static MESSAGES::BaseMessage* PopMessageQueue();
		static void PushMessageQueue(MESSAGES::BaseMessage* message);
		static bool isMessageQueueEmpty();

		// Mutex Operation
		static void MutexLock(std::mutex &mutex);
		static void MutexUnlock(std::mutex &mutex);

		// Get Mutex References
		static std::mutex &GetAmIMaster_Mutex();
		static std::mutex &GetMasterIP_Mutex();
		static std::mutex &GetNetworkIPs_Mutex();
		static std::mutex &GetMessageQueue_Mutex();
	};

}
#endif