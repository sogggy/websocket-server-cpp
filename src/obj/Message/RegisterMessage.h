//
// Created by Chew Song Yu on 23/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_REGISTERMESSAGE_H
#define WEBSOCKET_SERVER_CPP_REGISTERMESSAGE_H

#include <memory>
#include <json/json.h>

#include "Message.h"
#include "constants/messageTypes.h"

class RegisterMessage: public Message {
public:
    explicit RegisterMessage(const Json::Value& json);
    RegisterMessage() = delete;
    RegisterMessage& operator=(Json::Value json);
    static std::unique_ptr<RegisterMessage> createMessage(const Json::Value& json);
    Json::Value toJson() override;

protected:
    void print(std::ostream& out) const override;
};


#endif //WEBSOCKET_SERVER_CPP_REGISTERMESSAGE_H
