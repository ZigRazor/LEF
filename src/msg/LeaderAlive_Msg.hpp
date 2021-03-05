#ifndef LEADERALIVE_MSG_H
#define LEADERALIVE_MSG_H
#pragma once

#include "BaseMessage.hpp"

namespace MESSAGES
{
	class LeaderAlive_Msg : public BaseMessage
	{
	private:
	public:		
		LeaderAlive_Msg();
		~LeaderAlive_Msg();

		static const unsigned int MSG_ID = 2001;

		bool SerializeToOstream(std::ostream* output) const;
		bool ParseFromIstream(std::istream* input);	
		void FillHeader(std::string senderIP);

	};
}
#endif