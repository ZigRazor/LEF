#ifndef LEADERALIVEMSG_HANDLER_H
#define LEADERALIVEMSG_HANDLER_H
#pragma once

#include "msg/LeaderAlive_Msg.hpp"

namespace HANDLER
{

	class LeaderAliveMsg_Handler
	{
	private:
	public:
		LeaderAliveMsg_Handler() = delete;
		~LeaderAliveMsg_Handler() = delete;

		static void handlerLeaderAliveMsg(MESSAGES::LeaderAlive_Msg *message);
	};
}
#endif