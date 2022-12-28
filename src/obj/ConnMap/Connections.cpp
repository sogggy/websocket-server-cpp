//
// Created by Chew Song Yu on 23/12/22.
//

#include "Connections.h"

void Connections::push_safe(Connection conn) {
    mutex.lock();
    connections.push_back(conn);
    mutex.unlock();
}

void Connections::remove_safe(Connection& conn) {
    // on top of removing the desired connection, eagerly clean up all dangling pointers
    mutex.lock();
    auto i = connections.begin();
    while (i != connections.end()) {
        if (i->expired() || conn.lock() == i->lock()) {
            i = connections.erase(i);
            continue;
        }
        ++i;
    }
    mutex.unlock();
}

std::ostream& operator<<(std::ostream& out, Connections& conns) {
    out << "[ ";
    conns.mutex.lock_shared();
    for (auto& it : conns.connections) {
        out << it.lock().get() << ", ";
    }
    conns.mutex.unlock_shared();
    out << "] ";
    return out;
}
