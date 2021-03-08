#ifndef CHANNEL_H
#define CHANNEL_H
#pragma once
#include <string>

namespace CHANNEL
{
	class Channel
	{
	private:
		std::string IP;
		unsigned int port;
	public:
		Channel(std::string IP, unsigned int port);
		~Channel();
		std::string GetIP() const ;
		unsigned int  GetPort() const ;
	};
}
#endif