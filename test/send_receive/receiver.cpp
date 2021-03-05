#include "connection/UDPConnectionCustomer.hpp"
#include "msg/MessageHeader.hpp"
#include <iostream>
#include <sstream>

int main(){
    CONNECTION::UDPConnectionCustomer customer;
    customer.init("127.0.0.1",4001);
    customer.connect();
    char buffer[MAXMSGSIZE];
    customer.receiveMessage(buffer,MAXMSGSIZE);
    std::cout << buffer << std::endl;

    unsigned short len = customer.receiveMessage(buffer,MAXMSGSIZE);
    MESSAGES::MessageHeader message;
    std::istringstream input(buffer);
    //std::string buffer_string = buffer;
    //input << buffer_string;
    message.ParseFromIstream(&input);

    std::cout << "MessageId : " << message.GetMessageId() << std::endl;
    std::cout << "Time : " << message.GetTime() << std::endl;
    std::cout << "Sender IP (string): " << message.GetSenderIP_s() << std::endl;
    std::cout << "Sender IP (int): " << message.GetSenderIP() << std::endl;
    std::cout << "Data Size : " << message.GetDataSize() << std::endl;

    std::cout << buffer << std::endl;
    return 0;
}