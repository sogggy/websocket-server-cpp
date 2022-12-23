//
// Created by Chew Song Yu on 22/12/22.
//

#include "MessagesQueue.h"

void MessagesQueue::push_back_safe(Message* message) {
    mutex.lock();
    messagesQueue.push_back(message);
    mutex.unlock();
}

Message* MessagesQueue::pop_front_safe() {
    mutex.lock();
    Message* message = messagesQueue.front();
    messagesQueue.pop_front();
    mutex.unlock();
    return message;
}

std::ostream& operator<<(std::ostream& out, MessagesQueue& queue) {
    out << "[ ";
    queue.mutex.lock_shared();
    for (int i = 0; i < queue.messagesQueue.size(); i++) {
        out << *queue.messagesQueue[i] << " ";
    }
    queue.mutex.unlock_shared();
    out << "]" << std::endl;
    return out;
}
