//
// Created by Chew Song Yu on 20/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
#define WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <boost/asio.hpp>

typedef websocketpp::server<websocketpp::config::asio> WebsocketEndpoint;

class WebsocketServer {
private:
    WebsocketEndpoint endpoint;
    websocketpp::lib::asio::io_service eventLoop;
    int numConnections{ 0 };
    bool running{ false };

public:
    WebsocketServer();
    ~WebsocketServer();
    void run(int port);
};

#endif //WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
