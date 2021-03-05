#include "connection/UDPConnectionCustomer.hpp"
#include "msg/MessageHeader.hpp"
#include "msg/ConnectToNet_Msg.hpp"
#include <iostream>
#include <sstream>

void sendHello(CONNECTION::UDPConnectionCustomer* customer){
    char buffer[6];
    buffer[0] = 'H';
    buffer[1] = 'E';
    buffer[2] = 'L';
    buffer[3] = 'L';
    buffer[4] = 'O';
    buffer[5] = '\0';
    customer->sendMessage(buffer,6,"127.0.0.1",4001);
}

void sendGenericMessage(CONNECTION::UDPConnectionCustomer* customer){
    MESSAGES::MessageHeader message;
    message.SetCurrentTime();
    message.SetSenderIP_s("127.0.0.1");
    message.SetMessageId(21);
    message.SetDataSize(0);
    std::ostringstream  output;
    message.SerializeToOstream(&output);
    customer->sendMessage(output.str().c_str(),output.str().size(),"127.0.0.1",4001);
}

void sendConnectToNetMessage(CONNECTION::UDPConnectionCustomer* customer){
    MESSAGES::ConnectToNet_Msg message;
    message.FillHeader("127.0.0.1");
    std::ostringstream  output;
    message.SerializeToOstream(&output);
    customer->sendMessage(output.str().c_str(),output.str().size(),"127.0.0.1",4001);
}



int main(){
    CONNECTION::UDPConnectionCustomer customer;
    customer.init("127.0.0.1",4000);
    customer.connect();
    sockaddr_in sendAddress;
    
    sendConnectToNetMessage(&customer);
   
    return 0;
}