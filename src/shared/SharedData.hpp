#ifndef SHAREDDATA_H
#define SHAREDDATA_H
#pragma once

#include <mutex>
#include <set>
#include <queue>
#include <condition_variable>
#include "msg/BaseMessage.hpp"

namespace SHARED
{

	class SharedData
	{
	private:
		static bool amIMaster;
		static int masterIP;
		static std::set<int> networkIPs;
		static bool startingDataUpdated;

		//Queue
		static std::queue<MESSAGES::BaseMessage*> messageQueue;
		static std::queue<MESSAGES::BaseMessage*> toSendQueue;

		// Mutex
		static std::mutex m_amIMaster;
		static std::mutex m_masterIP;
		static std::mutex m_networkIPs;
		static std::mutex m_startingDataUpdated;
		static std::mutex m_messageQueue;
		static std::mutex m_toSendQueue;

		// Conditional Variable

		static std::condition_variable cv_messageQueue;
		static std::condition_variable cv_toSendQueue;
		static std::condition_variable cv_startingDataUpdated;

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
		static bool GetStartingDataUpdated();
		static void SetStartingDataUpdated(bool _startingDataUpdated);
		static void AddElementToNetworkIPs(int networkIP);
		static void DeleteElementFromNetworkIPs(int networkIP);

		// Queue Operation
		static MESSAGES::BaseMessage* PopMessageQueue();
		static void PushMessageQueue(MESSAGES::BaseMessage* message);
		static bool isMessageQueueEmpty();

		static MESSAGES::BaseMessage* PopToSendQueue();
		static void PushToSendQueue(MESSAGES::BaseMessage* message);
		static bool isToSendQueueEmpty();

		// Mutex Operation
		static void MutexLock(std::mutex &mutex);
		static void MutexUnlock(std::mutex &mutex);

		// Conditional Variable Operation
		static void CVWait(std::condition_variable &cv, std::mutex &mutex);
		static int CVWaitFor(std::condition_variable &cv, std::mutex &mutex, unsigned int timeout_ms);
		static void CVNotifyAll(std::condition_variable &cv);
		static void CVNotifyOne(std::condition_variable &cv);

		// Get Mutex References
		static std::mutex &GetAmIMaster_Mutex();
		static std::mutex &GetMasterIP_Mutex();
		static std::mutex &GetNetworkIPs_Mutex();
		static std::mutex &GetStartingDataUpdated_Mutex();
		static std::mutex &GetMessageQueue_Mutex();
		static std::mutex &GetToSendQueue_Mutex();

		// Get Conditional Variable References
		static std::condition_variable &GetMessageQueue_CV();
		static std::condition_variable &GetToSendQueue_CV();
		static std::condition_variable &GetStartingDataUpdated_CV();

	};

}
#endif