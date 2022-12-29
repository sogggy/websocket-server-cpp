//
// Created by Chew Song Yu on 22/12/22.
//

#include "SafeQueue.h"

template <typename T>
void SafeQueue<T>::push_back_safe(std::unique_ptr<T> elem) {
    mutex.lock();
    queue.push_back(std::move(elem));
    mutex.unlock();
}

template <typename T>
std::unique_ptr<T> SafeQueue<T>::pop_front_safe() {
    mutex.lock();
    if (queue.size() == 0) {
        mutex.unlock();
        return nullptr;
    }

    std::unique_ptr<T> elem = std::move(queue.front());
    queue.pop_front();
    mutex.unlock();
    return elem;
}
