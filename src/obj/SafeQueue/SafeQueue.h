//
// Created by Chew Song Yu on 22/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_SAFEQUEUE_H
#define WEBSOCKET_SERVER_CPP_SAFEQUEUE_H

#include <deque>
#include <iostream>
#include <shared_mutex>

#include "obj/Message/Message.h"

template <typename T>
class SafeQueue {
private:
    std::deque<T*> queue;
    std::shared_mutex mutex;

public:
    SafeQueue() = default;
    SafeQueue(const SafeQueue& safeQueue) = delete;
    SafeQueue& operator=(SafeQueue& safeQueue) = delete;
    void push_back_safe(T* elem);
    T* pop_front_safe();

    friend std::ostream& operator<<(std::ostream& out, SafeQueue<T>& safeQueue) {
        out << "[ ";
        safeQueue.mutex.lock_shared();
        for (int i = 0; i < safeQueue.queue.size(); i++) {
            out << *safeQueue.queue[i] << " ";
        }
        safeQueue.mutex.unlock_shared();
        out << "]" << std::endl;
        return out;
    }
};


#endif //WEBSOCKET_SERVER_CPP_SAFEQUEUE_H
