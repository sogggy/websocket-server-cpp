//
// Created by Chew Song Yu on 23/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_TYPES_H
#define WEBSOCKET_SERVER_CPP_TYPES_H

#include <websocketpp/common/connection_hdl.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

using Connection = websocketpp::connection_hdl;
using WebsocketEndpoint = websocketpp::server<websocketpp::config::asio>;

#endif //WEBSOCKET_SERVER_CPP_TYPES_H
