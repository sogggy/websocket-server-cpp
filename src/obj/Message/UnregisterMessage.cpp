//
// Created by Chew Song Yu on 23/12/22.
//

#include "UnregisterMessage.h"

UnregisterMessage::UnregisterMessage(const Json::Value& json):
    Message{
        MessageType::UNREGISTER,
        json["databaseName"].asString(),
        json["tableName"].asString(),
    } {}

UnregisterMessage* UnregisterMessage::createMessage(const Json::Value& json) {
    return new UnregisterMessage(json);
}

UnregisterMessage& UnregisterMessage::operator=(Json::Value json) {
    this->databaseName = json["databaseName"].asString();
    this->tableName = json["tableName"].asString();
    return *this;
}

Json::Value UnregisterMessage::toJson() {
    Json::Value root;
    root["type"] = "UNREGISTER";
    root["databaseName"] = databaseName;
    root["tableName"] = tableName;
    return root;
}

void UnregisterMessage::print(std::ostream& out) const {
    out << "{ " << std::endl
        << "messageType: " << messageType::UNREGISTER << ", " << std::endl
        << "databaseName: " << databaseName << ", " << std::endl
        << "tableName: " << tableName << ", " << std::endl;
}
