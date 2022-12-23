//
// Created by Chew Song Yu on 20/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
#define WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <boost/asio.hpp>
#include <json/value.h>
#include "obj/MessagesMap/MessagesMap.h"

typedef websocketpp::server<websocketpp::config::asio> WebsocketEndpoint;
typedef websocketpp::connection_hdl Connection;

class WebsocketServer {
private:
    bool running{ false };
    int numConnections;
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

    WebsocketEndpoint& getEndpoint() { return endpoint; }
    MessagesMap& getMessagesMap() { return messagesMap; }

    void run(int port);
    static Json::Value parseJson(const std::string& jsonString);
    static std::string stringifyJson(const Json::Value& json);
};

#endif //WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
