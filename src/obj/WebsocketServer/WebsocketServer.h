//
// Created by Chew Song Yu on 20/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
#define WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H

#include <boost/asio.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <json/value.h>

#include "obj/MessagesMap/MessagesMap.h"
#include "obj/ConnMap/ConnMap.h"
#include "types/types.h"

class WebsocketServer {
private:
    bool running{ false };
    int numConnections;
    ConnMap connMap;
    MessagesMap messagesMap;
    std::shared_mutex mutex;

    std::function<void(Connection conn)> onOpen;
    std::function<void(Connection conn)> onClose;
    std::function<void(Connection conn, WebsocketEndpoint::message_ptr msg)> onMessage;

    WebsocketEndpoint endpoint;
    websocketpp::lib::asio::io_service eventLoop;

public:
    WebsocketServer();
    ~WebsocketServer();
    WebsocketServer(const WebsocketServer& server) = delete;
    WebsocketServer& operator=(const WebsocketServer& server) = delete;

    const WebsocketEndpoint& getEndpoint() { return endpoint; }
    const MessagesMap& getMessagesMap() { return messagesMap; }
    const ConnMap& getConnMap() { return connMap; }

    void handleMessage(Message* message, Connection conn);

    void run(int port);
    static Json::Value parseJson(const std::string& jsonString);
    static std::string stringifyJson(const Json::Value& json);
};

#endif //WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
