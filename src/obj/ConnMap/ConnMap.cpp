//
// Created by Chew Song Yu on 23/12/22.
//

#include "ConnMap.h"

void ConnMap::push_safe(const std::string& id, Connection conn) {
    mutex.lock();
    if (connMap.find(id) == connMap.end()) {
        connMap.insert({ id, std::make_unique<Connections>()});
    }
    mutex.unlock();
    connMap[id]->push_safe(conn);
}

void ConnMap::remove_safe(const std::string& id, Connection conn) {
    mutex.lock_shared();
    if (connMap.find(id) == connMap.end()) {
        mutex.unlock_shared();
        return ;
    }

    auto& connections = connMap[id];
    mutex.unlock_shared();
    connections->remove_safe(conn);
}

void ConnMap::publish(const std::string& id, std::unique_ptr<Message> message) {
    mutex.lock_shared();
    std::unique_ptr<Connections>& connections = connMap[id];
    mutex.unlock_shared();
    connections->publish_safe(endpoint, std::move(message));
}

std::ostream& operator<<(std::ostream& out, ConnMap& conn) {
    out << "{" << std::endl;
    conn.mutex.lock_shared();
    for (auto& it : conn.connMap) {
        out << it.first << ": " << *it.second << std::endl;
    }
    conn.mutex.unlock_shared();
    out << "}" << std::endl;
    return out;
}