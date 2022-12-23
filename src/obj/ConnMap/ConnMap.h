//
// Created by Chew Song Yu on 23/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_CONNMAP_H
#define WEBSOCKET_SERVER_CPP_CONNMAP_H

#include <iostream>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "types/types.h"
#include "Connections.h"

class ConnMap {
private:
    std::unordered_map<std::string, Connections*> connMap;
    std::shared_mutex mutex;

public:
    ConnMap() = default;
    ConnMap& operator=(const ConnMap& connMap) = delete;
    ConnMap(const ConnMap& connMap) = delete;

    friend std::ostream& operator<<(std::ostream& out, ConnMap& conn);
    void push_safe(std::string id, Connection conn);
    void remove_safe(std::string id, Connection conn);
};


#endif //WEBSOCKET_SERVER_CPP_CONNMAP_H
