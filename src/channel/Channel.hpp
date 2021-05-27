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

		Channel(E_CommunicationType communicationType, std::string IP, unsigned int port);
		~Channel();
		E_CommunicationType GetCommunicationType() const;
		std::string GetIP() const;
		unsigned int GetPort() const;

	private:
		E_CommunicationType communicationType;
		std::string IP;
		unsigned int port;
	};
}
#endif