#ifndef CONNECTTONET_MSG_H
#define CONNECTTONET_MSG_H
#pragma once

#include "BaseMessage.hpp"

namespace MESSAGES
{
	class ConnectToNet_Msg : public BaseMessage
	{
	private:
	public:		
		ConnectToNet_Msg();
		~ConnectToNet_Msg();

		static const unsigned int MSG_ID = 1001;		

		bool SerializeToOstream(std::ostream* output) const;
		bool ParseFromIstream(std::istream* input);	
		void FillHeader(const std::string senderIP);

	};
}
#endif