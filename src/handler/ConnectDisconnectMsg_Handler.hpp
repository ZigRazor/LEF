#ifndef CONNECTDISCONNECTMSG_HANDLER_H
#define CONNECTDISCONNECTMSG_HANDLER_H
#pragma once

#include "msg/ConnectToNet_Msg.hpp"
#include "msg/DisconnectFromNet_Msg.hpp"

namespace HANDLER
{

	class ConnectDisconnectMsg_Handler
	{
	private:
	public:
		ConnectDisconnectMsg_Handler() = delete;
		~ConnectDisconnectMsg_Handler() = delete;

		static void handleConnectToNetMsg(MESSAGES::ConnectToNet_Msg *message);
		static void handleDisconnectFromNetMsg(MESSAGES::DisconnectFromNet_Msg *message);
	};

}
#endif