#ifndef BASEMESSAGE_H
#define BASEMESSAGE_H
#pragma once
#include "MessageHeader.hpp"
#include <sstream>

namespace MESSAGES
{

    class BaseMessage : public Serializable
    {
    protected:
        MessageHeader header;
        std::string MSG_CHANNEL;

        virtual unsigned int calculateDataSize() const;
    public:        

        BaseMessage() = default;
        virtual ~BaseMessage() = default;
        BaseMessage(char *buffer);

        MessageHeader GetHeader() const;
        void SetHeader(MessageHeader header);
        virtual void FillHeader();

        virtual bool SerializeToOstream(std::ostream* output) const;
        virtual bool ParseFromIstream(std::istream* input);

    };
}

#endif