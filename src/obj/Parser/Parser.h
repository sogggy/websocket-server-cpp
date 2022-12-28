//
// Created by Chew Song Yu on 21/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_PARSER_H
#define WEBSOCKET_SERVER_CPP_PARSER_H

#include <json/value.h>
#include "constants/messageTypes.h"
#include "obj/Message/UpdateRowMessage.h"
#include "obj/Message/Message.h"
#include "obj/Message/RegisterMessage.h"
#include "obj/Message/UnregisterMessage.h"

namespace Parser {
    Message* parsePublishMessage(const Json::Value& json);

    inline std::string getMethodRoute(const Json::Value& json) {
        return json["method"].asString() + " " + json["route"].asString();
    }

    inline Message* parseMessage(const Json::Value& json) {
        std::string type = json["type"].asString();
        std::string_view typeSv = type;
        if (typeSv == messageType::PUBLISH) {
            return parsePublishMessage(json);
        } else if (typeSv == messageType::REGISTER) {
            return RegisterMessage::createMessage(json);
        } else if (typeSv == messageType::UNREGISTER) {
            return UnregisterMessage::createMessage(json);
        } else {
            throw std::runtime_error("Unknown message type!");
        }
    }

    inline Message* parsePublishMessage(const Json::Value& json) {
        std::string methodRoute = getMethodRoute(json);
        std::string_view methodRouteSv = methodRoute;
        if (methodRouteSv == publishMessageType::ROW_UPDATE) {
            return UpdateRowMessage::createMessage(json);
        } else {
            throw std::runtime_error("Unknown publish message type!");
        }
    }

    inline Json::Value parseJsonString(const std::string& jsonString) {
        Json::Value root;
        Json::Reader reader;
        bool success = reader.parse(jsonString, root);
        if (!success) {
            std::clog << "Json parse failed for " << jsonString << std::endl;
            // TODO: throw error and log failure somewhere
        }
        return root;
    }

    inline std::string stringifyJson(const Json::Value& json) {
        Json::StreamWriterBuilder wbuilder;
        wbuilder["commentStyle"] = "None";
        wbuilder["indentation"] = "";

        return Json::writeString(wbuilder, json);
    }
}

#endif // WEBSOCKET_SERVER_CPP_PARSER_H
