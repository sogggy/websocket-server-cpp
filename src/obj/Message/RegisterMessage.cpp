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

RegisterMessage* RegisterMessage::createMessage(const Json::Value& json) {
    return new RegisterMessage(json);
}

void RegisterMessage::print(std::ostream& out) const {
    out << "{ "
        << "messageType: " << messageType::REGISTER << ", " << std::endl
        << "databaseName: " << databaseName << ", " << std::endl
        << "tableName: " << tableName << std::endl
        << " }";
}

RegisterMessage& RegisterMessage::operator=(const Json::Value json) {
    this->databaseName = json["databaseName"].asString();
    this->tableName = json["tableName"].asString();
    return *this;
}
