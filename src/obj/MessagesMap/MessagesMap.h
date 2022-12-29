//
// Created by Chew Song Yu on 22/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_MESSAGESMAP_H
#define WEBSOCKET_SERVER_CPP_MESSAGESMAP_H

#include <iostream>
#include <memory>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "obj/Message/Message.h"
#include "obj/SafeQueue/SafeQueue.h"
#include "types/types.h"

class MessagesMap {
private:
    std::unordered_map<std::string, std::unique_ptr<MessagesQueue>> messageMap;
    std::shared_mutex mutex;

public:
    MessagesMap() = default;
    MessagesMap(MessagesMap& messagesMap) = delete;
    MessagesMap& operator=(MessagesMap& messagesMap) = delete;
    void push(std::unique_ptr<Message> message);
    std::unique_ptr<Message> getMessage(const std::string& id);
    friend std::ostream& operator<<(std::ostream& out, MessagesMap& map);
};


#endif //WEBSOCKET_SERVER_CPP_MESSAGESMAP_H
