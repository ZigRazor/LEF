#ifndef MESSAGEHEADER_H
#define MESSAGEHEADER_H
#pragma once

#include <string>
#include <iostream>
#include <arpa/inet.h>
#include "Serializable.hpp"

namespace MESSAGES
{

	class MessageHeader : public Serializable
	{
	private:
		uint64_t time; //microseconds
		unsigned int senderIP; 
		unsigned int messageId;
		unsigned int dataSize;
	public:
		MessageHeader();
		~MessageHeader();
		unsigned int GetMessageId() const;
		void SetMessageId(unsigned int messageId);
		std::string GetSenderIP_s() const;
		void SetSenderIP_s(std::string senderIP);
		unsigned int GetSenderIP() const;
		void SetSenderIP(unsigned int senderIP);
		uint64_t GetTime() const;
		void SetTime(uint64_t time);
		void SetCurrentTime();
		unsigned int GetDataSize() const;
		void SetDataSize(unsigned int dataSize);
		bool SerializeToOstream(std::ostream* output) const;
		bool ParseFromIstream(std::istream* input);
		
	};

}
#endif