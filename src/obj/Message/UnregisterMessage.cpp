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

UnregisterMessage& UnregisterMessage::operator=(const Json::Value json) {
    this->databaseName = json["databaseName"].asString();
    this->tableName = json["tableName"].asString();
    return *this;
}

void UnregisterMessage::print(std::ostream& out) const {
    out << "{ " << std::endl
        << "messageType: " << messageType::UNREGISTER << ", " << std::endl
        << "databaseName: " << databaseName << ", " << std::endl
        << "tableName: " << tableName << ", " << std::endl;
}
