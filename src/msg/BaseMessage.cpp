#include "BaseMessage.hpp"

namespace MESSAGES
{
    BaseMessage::BaseMessage(char *buffer)
    {
        std::istringstream input(buffer);
        BaseMessage::ParseFromIstream(&input);
    }

    void BaseMessage::FillHeader()
    {
        //Do Nothing
    }

    MessageHeader BaseMessage::GetHeader() const
    {
        return header;
    }

    void BaseMessage::SetHeader(MessageHeader header)
    {
        header = header;
    }

    bool BaseMessage::SerializeToOstream(std::ostream *output) const
    {
        return header.SerializeToOstream(output);
        
    }
    bool BaseMessage::ParseFromIstream(std::istream *input)
    {
        return header.ParseFromIstream(input);
    }

    unsigned int BaseMessage::calculateDataSize() const{
        return 0;
    }

}