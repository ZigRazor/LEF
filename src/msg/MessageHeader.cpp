#include "MessageHeader.hpp"
#include "MessageConstant.hpp"

#include <chrono>

namespace MESSAGES
{

    MessageHeader::MessageHeader()
    {
    }

    MessageHeader::~MessageHeader()
    {
    }

    unsigned int MessageHeader::GetMessageId() const
    {
        return messageId;
    }

    void MessageHeader::SetMessageId(unsigned int messageId)
    {
        this->messageId = messageId;
    }

    std::string MessageHeader::GetSenderIP_s() const
    {
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(senderIP), str, INET_ADDRSTRLEN);
        return str;
    }

    void MessageHeader::SetSenderIP_s(std::string senderIP_s)
    {
        inet_pton(AF_INET, senderIP_s.c_str(), &(senderIP));
    }

    unsigned int MessageHeader::GetSenderIP() const
    {
        return senderIP;
    }

    void MessageHeader::SetSenderIP(unsigned int senderIP)
    {
        this->senderIP = senderIP;
    }

    std::string MessageHeader::GetReceiverIP_s() const
    {
        char str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(receiverIP), str, INET_ADDRSTRLEN);
        return str;
    }

    void MessageHeader::SetReceiverIP_s(std::string receiverIP_s)
    {
        inet_pton(AF_INET, receiverIP_s.c_str(), &(receiverIP));
    }

    unsigned int MessageHeader::GetReceiverIP() const
    {
        return receiverIP;
    }

    void MessageHeader::SetReceiverIP(unsigned int receiverIP)
    {
        this->receiverIP = receiverIP;
    }

    unsigned int MessageHeader::GetReceiverPort() const
    {
        return receiverPort;
    }

    void MessageHeader::SetReceiverPort(unsigned int receiverPort)
    {
        this->receiverPort = receiverPort;
    }

    uint64_t MessageHeader::GetTime() const
    {
        return time;
    }

    void MessageHeader::SetTime(uint64_t time)
    {
        this->time = time;
    }
    void MessageHeader::SetCurrentTime()
    {
        time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    unsigned int MessageHeader::GetDataSize() const
    {
        return dataSize;
    }

    void MessageHeader::SetDataSize(unsigned int dataSize)
    {
        this->dataSize = dataSize;
    }

    bool MessageHeader::SerializeToOstream(std::ostream *output) const
    {
        *output << time << FIELD_DELIMITER;
        *output << senderIP << FIELD_DELIMITER;
        *output << receiverIP << FIELD_DELIMITER;
        *output << receiverPort << FIELD_DELIMITER;
        *output << messageId << FIELD_DELIMITER;
        *output << dataSize << FIELD_DELIMITER;
        return true;
    }

    bool MessageHeader::ParseFromIstream(std::istream *input)
    {
        *input >> time;
        *input >> senderIP;
        *input >> receiverIP;
        *input >> receiverPort;
        *input >> messageId;
        *input >> dataSize;
        return true;
    }
}