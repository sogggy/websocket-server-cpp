//
// Created by Chew Song Yu on 21/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_MESSAGETYPES_H
#define WEBSOCKET_SERVER_CPP_MESSAGETYPES_H

#include <string_view>

enum class MessageType {
    PUBLISH, REGISTER, UNREGISTER,
};

namespace messageType {
    inline constexpr std::string_view PUBLISH = "PUBLISH";
    inline constexpr std::string_view REGISTER = "REGISTER"; // clients will register into a dataset to subscribe to updates
    inline constexpr std::string_view UNREGISTER = "UNREGISTER"; // clients will unregister from a dataset to unsubscribe to updates
}

enum class PublishMessageType {
    ROW_UPDATE,
};

// The websocket server will follow the REST API format of vault to identify the action.
namespace publishMessageType {
    inline constexpr std::string_view ROW_UPDATE = "PUT tables/{tableName}/row";
}

#endif //WEBSOCKET_SERVER_CPP_MESSAGETYPES_H
