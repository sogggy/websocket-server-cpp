//
// Created by Chew Song Yu on 21/12/22.
//

#include <json/value.h>
#include "constants/messageTypes.h"
#include "obj/Message/UpdateCellMessage.h"


namespace Parser {
    Message* parseMessage(const Json::Value& json) {
        std::string type = json["type"].asString();
        std::string_view typeSv = type;
        if (typeSv == messageTypes::CELL_UPDATE) {
            return UpdateCellMessage::createMessage(json);
        } else {
            throw std::runtime_error("Unknown message type!");
        }
    }
}