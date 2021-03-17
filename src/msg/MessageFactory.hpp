#ifndef MESSAGEFACTORY_H
#define MESSAGEFACTORY_H
#pragma once

#include "logger/logger.hpp"
#include "BaseMessage.hpp"

namespace MESSAGES
{
	class MessageFactory
	{
	private:
	public:
		MessageFactory() = delete;
		~MessageFactory() = delete;

		static BaseMessage *CreateMessage(char *buffer);
		static void DeleteMessage(BaseMessage *message);
	};
}
#endif