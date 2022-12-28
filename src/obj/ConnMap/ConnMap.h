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
    WebsocketEndpoint* endpoint;
    std::unordered_map<std::string, std::unique_ptr<Connections>> connMap;
    std::shared_mutex mutex;

public:
    ConnMap() = delete;
    ConnMap(WebsocketEndpoint* endpoint): endpoint{ endpoint }{}
    ConnMap& operator=(const ConnMap& connMap) = delete;
    ConnMap(const ConnMap& connMap) = delete;

    friend std::ostream& operator<<(std::ostream& out, ConnMap& conn);
    void push_safe(const std::string& id, Connection conn);
    void remove_safe(const std::string& id, Connection conn);
    void publish(const std::string& id, Message* message);
};


#endif //WEBSOCKET_SERVER_CPP_CONNMAP_H
