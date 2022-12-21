//
// Created by Chew Song Yu on 21/12/22.
//

#include "Message.h"
#include <iostream>

void Message::print() const {
    std::cout << "Base message class" << std::endl;
}

Message* Message::createMessage(const Json::Value &json) {
    throw std::runtime_error("Error: Base message class method called!");
}
