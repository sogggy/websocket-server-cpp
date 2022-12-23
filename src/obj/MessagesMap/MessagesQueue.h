//
// Created by Chew Song Yu on 22/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_MESSAGESQUEUE_H
#define WEBSOCKET_SERVER_CPP_MESSAGESQUEUE_H

#include <deque>
#include <iostream>
#include <shared_mutex>

#include "obj/Message/Message.h"

class MessagesQueue {
private:
    std::deque<Message*> messagesQueue;
    std::shared_mutex mutex;

public:
    MessagesQueue() = default;
    MessagesQueue(const MessagesQueue& messagesQueue) = delete;
    MessagesQueue& operator=(MessagesQueue& messagesQueue) = delete;
    void push_back_safe(Message* message);
    Message* pop_front_safe();

    friend std::ostream& operator<<(std::ostream& out, MessagesQueue& queue);
};


#endif //WEBSOCKET_SERVER_CPP_MESSAGESQUEUE_H
