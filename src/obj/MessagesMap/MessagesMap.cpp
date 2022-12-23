//
// Created by Chew Song Yu on 22/12/22.
//

#include <iostream>
#include <string>

#include "MessagesMap.h"

void MessagesMap::push(Message* message) {
    std::string id = message->getId();
    mutex.lock();
    if (messageMap.find(id) == messageMap.end()) {
        messageMap.insert(std::pair<std::string, MessagesQueue*>(id, new MessagesQueue()));
    }
    mutex.unlock();
    messageMap[id]->push_back_safe(message);
}

std::ostream& operator<<(std::ostream& out, MessagesMap& map) {
    out << "{ " << std::endl;
    map.mutex.lock_shared();
    for (auto& it: map.messageMap) {
        out << it.first << ": " << *it.second << std::endl;
    }
    map.mutex.unlock_shared();
    out << "}" << std::endl;
    return out;
}

