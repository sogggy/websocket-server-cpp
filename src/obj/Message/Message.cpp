//
// Created by Chew Song Yu on 21/12/22.
//

#include "Message.h"

void Message::print(std::ostream& out) const {
    out << "Base message class" << std::endl;
}

Json::Value Message::toJson() {
    Json::Value root;
    return root;
}

Message* Message::createMessage(const Json::Value &json) {
    throw std::runtime_error("Error: Base message class method called!");
}
