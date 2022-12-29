//
// Created by Chew Song Yu on 21/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_UPDATEROWMESSAGE_H
#define WEBSOCKET_SERVER_CPP_UPDATEROWMESSAGE_H

#include <iostream>
#include <memory>
#include <json/json.h>
#include <json/value.h>
#include "Message.h"
#include "constants/messageTypes.h"

class UpdateRowMessage: public Message {
private:
    PublishMessageType publishMessageType;
    std::string columnAlias;
    std::string rowId;
    std::string newValue;

public:
    explicit UpdateRowMessage(const Json::Value& json);
    UpdateRowMessage() = delete;
    UpdateRowMessage& operator=(const Json::Value& json);
    static std::unique_ptr<UpdateRowMessage> createMessage(const Json::Value& json);
    Json::Value toJson() override;

protected:
    void print(std::ostream& out) const override;
};


#endif //WEBSOCKET_SERVER_CPP_UPDATEROWMESSAGE_H
