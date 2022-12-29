//
// Created by Chew Song Yu on 23/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_UNREGISTERMESSAGE_H
#define WEBSOCKET_SERVER_CPP_UNREGISTERMESSAGE_H

#include <memory>
#include <json/json.h>

#include "Message.h"
#include "constants/messageTypes.h"

class UnregisterMessage: public Message {
public:
    explicit UnregisterMessage(const Json::Value& json);
    UnregisterMessage() = delete;
    UnregisterMessage& operator=(Json::Value json);
    static std::unique_ptr<UnregisterMessage> createMessage(const Json::Value& json);
    Json::Value toJson() override;

protected:
    void print(std::ostream& out) const override;
};


#endif //WEBSOCKET_SERVER_CPP_UNREGISTERMESSAGE_H
