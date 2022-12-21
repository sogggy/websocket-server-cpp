//
// Created by Chew Song Yu on 21/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_UPDATECELLMESSAGE_H
#define WEBSOCKET_SERVER_CPP_UPDATECELLMESSAGE_H

#include "Message.h"

class UpdateCellMessage: public Message {
private:
    MessageType messageType{ MessageType::CELL_UPDATE };
    std::string columnName;
    std::string rowId;
    std::string newValue;
    std::string databaseName;
    std::string tableName;

public:
    UpdateCellMessage& operator=(const Json::Value& json);
    static UpdateCellMessage* createMessage(const Json::Value& json);

protected:
    void print() const;

private:
    UpdateCellMessage() = default;
    explicit UpdateCellMessage(const Json::Value& json);
};


#endif //WEBSOCKET_SERVER_CPP_UPDATECELLMESSAGE_H
