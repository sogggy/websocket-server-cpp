//
// Created by Chew Song Yu on 21/12/22.
//

#include "UpdateRowMessage.h"
#include "constants/messageTypes.h"
#include <iostream>

UpdateRowMessage::UpdateRowMessage(const Json::Value& json):
    Message{
        MessageType::PUBLISH,
        json["databaseName"].asString(), json["tableName"].asString()
    },
        publishMessageType{ PublishMessageType::ROW_UPDATE },
        columnName{ json["columnName"].asString() },
        rowId{ json["rowId"].asString() },
        newValue{ json["newValue"].asString(),
    } {}

void UpdateRowMessage::print(std::ostream& out) const {
    out << "{ " << std::endl
        << "messageType: ROW_UPDATE, " << std::endl
        << "databaseName: " << databaseName << ", " << std::endl
        << "tableName: " << tableName << ", " << std::endl
        << "columnName: " << columnName << ", " << std::endl
        << "rowId: " << rowId << ", " << std::endl
        << "newValue: " << newValue << std::endl
        << " }";
}

UpdateRowMessage* UpdateRowMessage::createMessage(const Json::Value& json) {
    return new UpdateRowMessage(json);
}

UpdateRowMessage& UpdateRowMessage::operator=(const Json::Value& json) {
    this->databaseName = json["databaseName"].asString();
    this->tableName = json["tableName"].asString();
    this->columnName = json["columnName"].asString();
    this->rowId = json["rowId"].asString();
    this->newValue = json["newValue"].asString();
    return *this;
}
