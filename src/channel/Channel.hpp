#ifndef CHANNEL_H
#define CHANNEL_H
#pragma once
#include <string>

namespace CHANNEL
{
	class Channel
	{
	public:
		typedef enum CommunicationType_Enumeration
		{
			INPROC,
			UDP,
			TCP
		} E_CommunicationType;

		Channel(const std::string& channelName, E_CommunicationType communicationType, const std::string& IP, unsigned int port);
		~Channel();
		const std::string& GetChannelName() const;
		E_CommunicationType GetCommunicationType() const;
		std::string GetIP() const;
		unsigned int GetPort() const;

	private:
		std::string channelName;
		E_CommunicationType communicationType;
		std::string IP;
		unsigned int port;
	};
}
#endif