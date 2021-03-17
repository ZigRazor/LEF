#ifndef STARTINGINFORMATIONREQUEST_MSG_H
#define STARTINGINFORMATIONREQUEST_MSG_H
#pragma once

#include "BaseMessage.hpp"

namespace MESSAGES
{

	class StartingInformationRequest_Msg : public BaseMessage
	{
	private:
	public:
		StartingInformationRequest_Msg();
		~StartingInformationRequest_Msg();

		static const unsigned int MSG_ID = 1003;

		bool SerializeToOstream(std::ostream *output) const;
		bool ParseFromIstream(std::istream *input);
		void FillHeader(const std::string senderIP);
	};

}
#endif