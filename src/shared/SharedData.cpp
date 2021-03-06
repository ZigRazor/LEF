#include "SharedData.hpp"
#include <algorithm>
#include <chrono>
#include "logger/logger.hpp"

using namespace std::chrono_literals;
namespace SHARED
{
    //static variable
    bool SharedData::amIMaster = false;
    int SharedData::masterIP = -1; // invalid initialization
    std::set<int> SharedData::networkIPs;
    bool SharedData::startingDataUpdated = false;

    //Queue
    std::queue<MESSAGES::BaseMessage *> SharedData::messageQueue;
    std::queue<MESSAGES::BaseMessage *> SharedData::toSendQueue;

    // Mutex
    std::mutex SharedData::m_amIMaster;
    std::mutex SharedData::m_masterIP;
    std::mutex SharedData::m_networkIPs;
    std::mutex SharedData::m_startingDataUpdated;
    std::mutex SharedData::m_messageQueue;
    std::mutex SharedData::m_toSendQueue;

    // Conditional Variable

    std::condition_variable SharedData::cv_messageQueue;
	std::condition_variable SharedData::cv_toSendQueue;
    std::condition_variable SharedData::cv_startingDataUpdated;


    int SharedData::GetMasterIP()
    {
        m_masterIP.lock();
        LOG(L_TRACE, "Get Master IP locked");
        int _masterIP = masterIP;
        m_masterIP.unlock();
        LOG(L_TRACE, "Get Master IP unlocked");
        return _masterIP;
    }

    void SharedData::SetMasterIP(int _masterIP)
    {
        m_masterIP.lock();
        masterIP = _masterIP;
        m_masterIP.unlock();
    }

    bool SharedData::GetAmIMaster()
    {
        m_amIMaster.lock();
        bool _amIMaster = amIMaster;
        m_amIMaster.unlock();
        return _amIMaster;
    }

    void SharedData::SetAmIMaster(bool _amIMaster)
    {
        m_amIMaster.lock();
        amIMaster = _amIMaster;
        m_amIMaster.unlock();
    }

    std::set<int> SharedData::GetNetworkIPs()
    {
        m_networkIPs.lock();
        std::set<int> _networkIPs = networkIPs;
        LOG(L_TRACE, "GetNetworkIPs locked");        
        m_networkIPs.unlock();
        LOG(L_TRACE, "GetNetworkIPs unlocked");   
        return _networkIPs;
    }

    void SharedData::SetNetworkIPs(std::set<int> _networkIPs)
    {
        m_networkIPs.lock();
        networkIPs = _networkIPs;
        m_networkIPs.unlock();
    }

    std::set<int> &SharedData::GetNetworkIPs_Ref()
    {
        // Should be muted by external call
        return networkIPs;
    }

    void SharedData::AddElementToNetworkIPs(int networkIP)
    {
        m_networkIPs.lock();
        networkIPs.insert(networkIP);
        m_networkIPs.unlock();
    }
    void SharedData::DeleteElementFromNetworkIPs(int networkIP)
    {
        m_networkIPs.lock();
        networkIPs.erase(std::find(networkIPs.begin(), networkIPs.end(), networkIP));
        m_networkIPs.unlock();
    }

    bool SharedData::GetStartingDataUpdated(){
        m_startingDataUpdated.lock();
        bool _startingDataUpdated = startingDataUpdated;
        m_startingDataUpdated.unlock();
        return _startingDataUpdated;
    }
	void SharedData::SetStartingDataUpdated(bool _startingDataUpdated){
        m_startingDataUpdated.lock();
        startingDataUpdated = _startingDataUpdated;
        m_startingDataUpdated.unlock();
    }

    MESSAGES::BaseMessage *SharedData::PopMessageQueue()
    {
        m_messageQueue.lock();
        MESSAGES::BaseMessage *message = messageQueue.front();
        messageQueue.pop();
        m_messageQueue.unlock();
        return message;
    }

    void SharedData::PushMessageQueue(MESSAGES::BaseMessage *message)
    {
        m_messageQueue.lock();
        messageQueue.push(message);
        m_messageQueue.unlock();
    }

    bool SharedData::isMessageQueueEmpty(){
        m_messageQueue.lock();
        bool empty = messageQueue.empty();
        m_messageQueue.unlock();
        return empty;
    }

    MESSAGES::BaseMessage *SharedData::PopToSendQueue()
    {
        m_toSendQueue.lock();
        MESSAGES::BaseMessage *message = toSendQueue.front();
        toSendQueue.pop();
        m_toSendQueue.unlock();
        return message;
    }

    void SharedData::PushToSendQueue(MESSAGES::BaseMessage *message)
    {
        m_toSendQueue.lock();
        toSendQueue.push(message);
        m_toSendQueue.unlock();
    }

    bool SharedData::isToSendQueueEmpty(){
        m_toSendQueue.lock();
        bool empty = toSendQueue.empty();
        m_toSendQueue.unlock();
        return empty;
    }

    void SharedData::MutexLock(std::mutex &mutex)
    {
        mutex.lock();
    }
    void SharedData::MutexUnlock(std::mutex &mutex)
    {
        mutex.unlock();
    }

    std::mutex &SharedData::GetAmIMaster_Mutex()
    {
        return m_amIMaster;
    }
    std::mutex &SharedData::GetMasterIP_Mutex()
    {
        return m_masterIP;
    }
    std::mutex &SharedData::GetNetworkIPs_Mutex()
    {
        return m_networkIPs;
    }

    std::mutex &SharedData::GetMessageQueue_Mutex()
    {
        return m_messageQueue;
    }

    std::mutex &SharedData::GetToSendQueue_Mutex()
    {
        return m_toSendQueue;
    }

    std::mutex &SharedData::GetStartingDataUpdated_Mutex()
    {
        return m_startingDataUpdated;
    }

    std::condition_variable &SharedData::GetMessageQueue_CV(){
        return cv_messageQueue;
    }

    std::condition_variable &SharedData::GetToSendQueue_CV(){
        return cv_toSendQueue;
    }

    std::condition_variable &SharedData::GetStartingDataUpdated_CV(){
        return cv_startingDataUpdated;
    }

    void SharedData::CVWait(std::condition_variable &cv, std::mutex &mutex){
            std::unique_lock<std::mutex> lk(mutex);
            cv.wait(lk);
    }

    int SharedData::CVWaitFor(std::condition_variable &cv, std::mutex &mutex, unsigned int timeout_ms){
            int result = 0;
            std::unique_lock<std::mutex> lk(mutex);
            //DEBUG auto start = std::chrono::system_clock::now();
            cv.wait_for(lk,timeout_ms*1ms);
            //DEBUG auto end = std::chrono::system_clock::now();
            //DEBUG std::cout << "waiting for " << (end -start).count() << std::endl;
            return result;
    }
	void SharedData::CVNotifyAll(std::condition_variable &cv){
            cv.notify_all();
    }
		
    void SharedData::CVNotifyOne(std::condition_variable &cv){
        cv.notify_one();
    }
}