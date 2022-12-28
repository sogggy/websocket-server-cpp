//
// Created by Chew Song Yu on 21/12/22.
//

#include "UpdateRowMessage.h"
#include "constants/messageTypes.h"

UpdateRowMessage::UpdateRowMessage(const Json::Value& json):
        Message{
        MessageType::PUBLISH,
        json["databaseName"].asString(),
        json["tableName"].asString(),
    },
        publishMessageType{ PublishMessageType::ROW_UPDATE },
        columnAlias{json["columnAlias"].asString() },
        rowId{ json["rowId"].asString() },
        newValue{ json["newValue"].asString(),
    } {}

Json::Value UpdateRowMessage::toJson() {
    Json::Value root;
    root["type"] = "PUBLISH";
    root["databaseName"] = databaseName;
    root["tableName"] = tableName;
    root["columnAlias"] = columnAlias;
    root["rowId"] = rowId;
    root["newValue"] = newValue;
    return root;
}

void UpdateRowMessage::print(std::ostream& out) const {
    out << "{ " << std::endl
        << "messageType: ROW_UPDATE, " << std::endl
        << "databaseName: " << databaseName << ", " << std::endl
        << "tableName: " << tableName << ", " << std::endl
        << "columnAlias: " << columnAlias << ", " << std::endl
        << "rowId: " << rowId << ", " << std::endl
        << "newValue: " << newValue << std::endl
        << "}";
}

UpdateRowMessage* UpdateRowMessage::createMessage(const Json::Value& json) {
    return new UpdateRowMessage(json);
}

UpdateRowMessage& UpdateRowMessage::operator=(const Json::Value& json) {
    this->databaseName = json["databaseName"].asString();
    this->tableName = json["tableName"].asString();
    this->columnAlias = json["columnAlias"].asString();
    this->rowId = json["rowId"].asString();
    this->newValue = json["newValue"].asString();
    return *this;
}
