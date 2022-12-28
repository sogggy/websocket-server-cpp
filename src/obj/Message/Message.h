//
// Created by Chew Song Yu on 21/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_MESSAGE_H
#define WEBSOCKET_SERVER_CPP_MESSAGE_H


#include <string>
#include <utility>
#include <json/value.h>
#include "constants/messageTypes.h"

class Message {
protected:
    MessageType messageType;
    std::string databaseName;
    std::string tableName;
    std::string id;
    Message(MessageType messageType, const std::string& databaseName, const std::string& tableName):
            messageType{ messageType },
            databaseName{ databaseName },
            tableName{ tableName },
            id { databaseName + "-" + tableName } {}

public:
    Message(Message& message) = delete;
    std::string getId() { return id; }
    MessageType getMessageType() { return messageType; }

protected:
    virtual void print(std::ostream& out) const;
    static Message* createMessage(const Json::Value& json);
    friend std::ostream& operator<<(std::ostream& out, const Message& message) {
        message.print(out);
        return out;
    }
};

#endif //WEBSOCKET_SERVER_CPP_MESSAGE_H
