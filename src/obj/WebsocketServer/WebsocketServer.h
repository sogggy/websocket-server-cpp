//
// Created by Chew Song Yu on 20/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
#define WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <boost/asio.hpp>
#include <json/value.h>

typedef websocketpp::server<websocketpp::config::asio> WebsocketEndpoint;
typedef websocketpp::connection_hdl Connection;

class WebsocketServer {
public:
    WebsocketServer();
    ~WebsocketServer();
    void run(int port);
    static Json::Value parseJson(const std::string& jsonString);
    static std::string stringifyJson(const Json::Value& json);

private:
    bool running{ false };
    int numConnections{ 0 };

    std::function<void(Connection conn)> onOpen;
    std::function<void(Connection conn)> onClose;
    std::function<void(Connection conn, WebsocketEndpoint::message_ptr msg)> onMessage;

    WebsocketEndpoint endpoint;
    websocketpp::lib::asio::io_service eventLoop;
};

#endif //WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
