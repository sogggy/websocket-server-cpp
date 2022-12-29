//
// Created by Chew Song Yu on 23/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_CONNECTIONS_H
#define WEBSOCKET_SERVER_CPP_CONNECTIONS_H

#include <iostream>
#include <shared_mutex>
#include <vector>

#include "types/types.h"

class Connections {
private:
    std::vector<Connection> connections;
    std::shared_mutex mutex;

public:
    Connections() = default;
    Connections(Connections& other) = delete;
    Connections& operator=(const Connections& other) = delete;

    friend std::ostream& operator<<(std::ostream& out, Connections& conns);

    void push_safe(Connection conn);
    void remove_safe(Connection& conn);
    void publish_safe(WebsocketEndpoint* endpoint, std::unique_ptr<Message> message);
};


#endif //WEBSOCKET_SERVER_CPP_CONNECTIONS_H
