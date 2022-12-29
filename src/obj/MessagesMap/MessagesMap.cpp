//
// Created by Chew Song Yu on 22/12/22.
//

#include "MessagesMap.h"

void MessagesMap::push(std::unique_ptr<Message> message) {
    std::string id = message->getId();
    mutex.lock();
    if (messageMap.find(id) == messageMap.end()) {
        messageMap.insert(std::pair<std::string,
                          std::unique_ptr<SafeQueue<Message>>>(id, std::make_unique<SafeQueue<Message>>()));
    }
    mutex.unlock();
    messageMap[id]->push_back_safe(std::move(message));
}

std::unique_ptr<Message> MessagesMap::getMessage(const std::string& id) {
    mutex.lock_shared();
    std::unique_ptr<MessagesQueue>& messagesQueue = messageMap[id];
    mutex.unlock_shared();
    return messagesQueue->pop_front_safe();
}

std::ostream& operator<<(std::ostream& out, MessagesMap& map) {
    out << "{ " << std::endl;
    map.mutex.lock_shared();
    for (auto& it: map.messageMap) {
        out << '\t' << it.first << ": " << *it.second << std::endl;
    }
    map.mutex.unlock_shared();
    out << "}" << std::endl;
    return out;
}

