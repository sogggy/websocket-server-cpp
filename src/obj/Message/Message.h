//
// Created by Chew Song Yu on 21/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_MESSAGE_H
#define WEBSOCKET_SERVER_CPP_MESSAGE_H


#include <string>
#include <utility>
#include <json/value.h>

enum class MessageType {
    CELL_UPDATE,
};

class Message {
protected:
    std::string databaseName;
    std::string tableName;
    Message(std::string databaseName, std::string tableName):
        databaseName{std::move( databaseName )}, tableName{std::move( tableName )} {}
    Message(Message& message) = default;

    virtual void print() const;
    static Message* createMessage(const Json::Value& json);
    friend std::ostream& operator<<(std::ostream& out, const Message& message) {
        message.print();
        return out;
    }

};

#endif //WEBSOCKET_SERVER_CPP_MESSAGE_H
