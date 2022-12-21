//
// Created by Chew Song Yu on 21/12/22.
//

#include "UpdateCellMessage.h"
#include <iostream>

UpdateCellMessage::UpdateCellMessage(const Json::Value& json):
    Message{ json["databaseName"].asString(), json["tableName"].asString() },
    messageType{ MessageType::CELL_UPDATE },
    columnName{ json["columnName"].asString() },
    rowId{ json["rowId"].asString() },
    newValue{ json["newValue"].asString() } {}

void UpdateCellMessage::print() const {
    std::cout << "{ " << "messageType: CELL_UPDATE, " << "databaseName: " << databaseName << ", "
    << "tableName: " << tableName << ", " << "columnName: " << columnName << ", " << "rowId: " << rowId << ", "
    << "newValue: " << newValue << " }";
}

UpdateCellMessage* UpdateCellMessage::createMessage(const Json::Value& json) {
    return new UpdateCellMessage(json);
}

UpdateCellMessage& UpdateCellMessage::operator=(const Json::Value& json) {
    this->databaseName = json["databaseName"].asString();
    this->tableName = json["tableName"].asString();
    this->columnName = json["columnName"].asString();
    this->rowId = json["rowId"].asString();
    this->newValue = json["newValue"].asString();
    return *this;
}
