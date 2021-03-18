#ifndef STARTINGINFORMATION_MSG_H
#define STARTINGINFORMATION_MSG_H
#pragma once

#include "BaseMessage.hpp"
#include <set>

namespace MESSAGES
{
	class StartingInformation_Msg : public BaseMessage
	{
	private:
		int masterIP;
		unsigned int numberOfnetworkIP;
		std::set<int> networkIPs;

		unsigned int calculateDataSize() const; 

	public:
		StartingInformation_Msg();
		~StartingInformation_Msg();

		static const unsigned int MSG_ID = 1004;

		bool SerializeToOstream(std::ostream *output) const;
		bool ParseFromIstream(std::istream *input);
		void FillHeader(const std::string senderIP);

		int GetMasterIP() const;
		void SetMasterIP(int masterIP);
		unsigned int GetNumberOfnetworkIP() const;
		//void SetNumberOfnetworkIP(unsigned int numberOfnetworkIP);
		std::set<int> GetNetworkIPs() const;
		void SetNetworkIPs(std::set<int> networkIPs);
	};

}

#endif