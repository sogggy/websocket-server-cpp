//
// Created by Chew Song Yu on 23/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_TYPES_H
#define WEBSOCKET_SERVER_CPP_TYPES_H

#include <websocketpp/common/connection_hdl.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

#include "obj/Message/Message.h"
#include "obj/SafeQueue/SafeQueue.h"

using Connection = websocketpp::connection_hdl;
using WebsocketEndpoint = websocketpp::server<websocketpp::config::asio>;
using MessagesQueue = SafeQueue<Message>;
using Jobs = SafeQueue<std::string>;

#endif //WEBSOCKET_SERVER_CPP_TYPES_H
