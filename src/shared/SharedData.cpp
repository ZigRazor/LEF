#include "SharedData.hpp"
#include <algorithm>

namespace SHARED
{
    //static variable
    bool SharedData::amIMaster = false;
    int SharedData::masterIP = -1;
    std::set<int> SharedData::networkIPs;

    //Queue
    std::queue<MESSAGES::BaseMessage *> SharedData::messageQueue;

    // Mutex
    std::mutex SharedData::m_amIMaster;
    std::mutex SharedData::m_masterIP;
    std::mutex SharedData::m_networkIPs;
    std::mutex SharedData::m_messageQueue;

    int SharedData::GetMasterIP()
    {
        m_masterIP.lock();
        int _masterIP = masterIP;
        m_masterIP.unlock();
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
        return networkIPs;
        m_networkIPs.unlock();
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
}