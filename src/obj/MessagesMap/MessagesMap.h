//
// Created by Chew Song Yu on 22/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_MESSAGESMAP_H
#define WEBSOCKET_SERVER_CPP_MESSAGESMAP_H

#include <iostream>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "obj/Message/Message.h"
#include "obj/SafeQueue/SafeQueue.h"

class MessagesMap {
private:
    std::unordered_map<std::string, SafeQueue<Message>*> messageMap;
    std::shared_mutex mutex;

public:
    MessagesMap() = default;
    MessagesMap(MessagesMap& messagesMap) = delete;
    MessagesMap& operator=(MessagesMap& messagesMap) = delete;
    void push(Message* message);
    friend std::ostream& operator<<(std::ostream& out, MessagesMap& map);
};


#endif //WEBSOCKET_SERVER_CPP_MESSAGESMAP_H
