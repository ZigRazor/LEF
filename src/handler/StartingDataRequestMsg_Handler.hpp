#ifndef STARTINGDATAREQUESTMSG_HANDLER_H
#define STARTINGDATAREQUESTMSG_HANDLER_H
#pragma once
#include "msg/StartingInformationRequest_Msg.hpp"

namespace HANDLER
{

	class StartingDataRequestMsg_Handler
	{
	private:
	public:
		StartingDataRequestMsg_Handler() = delete;
		~StartingDataRequestMsg_Handler() = delete;

		static void handlerStartingInformationRequestMsg(MESSAGES::StartingInformationRequest_Msg *message);
	};

}
#endif