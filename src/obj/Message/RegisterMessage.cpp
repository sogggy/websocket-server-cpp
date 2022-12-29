//
// Created by Chew Song Yu on 23/12/22.
//

#include "RegisterMessage.h"

RegisterMessage::RegisterMessage(const Json::Value& json):
        Message {
        MessageType::REGISTER,
        json["databaseName"].asString(),
        json["tableName"].asString(),
        } {}

std::unique_ptr<RegisterMessage> RegisterMessage::createMessage(const Json::Value& json) {
    return std::make_unique<RegisterMessage>(json);
}

Json::Value RegisterMessage::toJson() {
    Json::Value root;
    root["type"] = "REGISTER";
    root["databaseName"] = databaseName;
    root["tableName"] = tableName;
    return root;
}

void RegisterMessage::print(std::ostream& out) const {
    out << "{ "
        << "messageType: " << messageType::REGISTER << ", "
        << "databaseName: " << databaseName << ", "
        << "tableName: " << tableName
        << " }";
}

RegisterMessage& RegisterMessage::operator=(Json::Value json) {
    this->databaseName = json["databaseName"].asString();
    this->tableName = json["tableName"].asString();
    return *this;
}
