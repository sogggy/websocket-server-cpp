//
// Created by Chew Song Yu on 22/12/22.
//

#include "SafeQueue.h"

template <typename T>
void SafeQueue<T>::push_back_safe(T* elem) {
    mutex.lock();
    queue.push_back(elem);
    mutex.unlock();
}

template <typename T>
T* SafeQueue<T>::pop_front_safe() {
    mutex.lock();
    T* elem = queue.front();
    queue.pop_front();
    mutex.unlock();
    return elem;
}
