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
    out << "{ "
        << "messageType: ROW_UPDATE, "
        << "databaseName: " << databaseName << ", "
        << "tableName: " << tableName << ", "
        << "columnAlias: " << columnAlias << ", "
        << "rowId: " << rowId << ", "
        << "newValue: " << newValue
        << " }";
}

std::unique_ptr<UpdateRowMessage> UpdateRowMessage::createMessage(const Json::Value& json) {
    return std::make_unique<UpdateRowMessage>(json);
}

UpdateRowMessage& UpdateRowMessage::operator=(const Json::Value& json) {
    this->databaseName = json["databaseName"].asString();
    this->tableName = json["tableName"].asString();
    this->columnAlias = json["columnAlias"].asString();
    this->rowId = json["rowId"].asString();
    this->newValue = json["newValue"].asString();
    return *this;
}
