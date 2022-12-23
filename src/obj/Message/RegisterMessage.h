//
// Created by Chew Song Yu on 23/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_REGISTERMESSAGE_H
#define WEBSOCKET_SERVER_CPP_REGISTERMESSAGE_H

#include "Message.h"
#include "constants/messageTypes.h"

class RegisterMessage: public Message {
private:
    MessageType messageType;
    RegisterMessage() = delete;
    explicit RegisterMessage(const Json::Value& json);

public:
    RegisterMessage& operator=(const Json::Value json);
    static RegisterMessage* createMessage(const Json::Value& json);

protected:
    void print(std::ostream& out) const override;
};


#endif //WEBSOCKET_SERVER_CPP_REGISTERMESSAGE_H
