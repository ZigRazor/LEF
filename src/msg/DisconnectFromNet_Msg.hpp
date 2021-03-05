#ifndef DISCONNECTFROMNET_MSG_H
#define DISCONNECTFROMNET_MSG_H
#pragma once

#include "BaseMessage.hpp"

namespace MESSAGES
{
	class DisconnectFromNet_Msg : public BaseMessage
	{
	private:
	public:		
		DisconnectFromNet_Msg();
		~DisconnectFromNet_Msg();

		static const unsigned int MSG_ID = 1002;

		bool SerializeToOstream(std::ostream* output) const;
		bool ParseFromIstream(std::istream* input);	
		void FillHeader(std::string senderIP);

	};
}
#endif