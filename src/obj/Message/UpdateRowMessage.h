//
// Created by Chew Song Yu on 21/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_UPDATEROWMESSAGE_H
#define WEBSOCKET_SERVER_CPP_UPDATEROWMESSAGE_H

#include <iostream>
#include <json/value.h>
#include "Message.h"
#include "constants/messageTypes.h"

class UpdateRowMessage: public Message {
private:
    PublishMessageType publishMessageType;
    std::string columnName;
    std::string rowId;
    std::string newValue;

    UpdateRowMessage() = delete;
    explicit UpdateRowMessage(const Json::Value& json);

public:
    UpdateRowMessage& operator=(const Json::Value& json);
    static UpdateRowMessage* createMessage(const Json::Value& json);

protected:
    void print(std::ostream& out) const override;
};


#endif //WEBSOCKET_SERVER_CPP_UPDATEROWMESSAGE_H
