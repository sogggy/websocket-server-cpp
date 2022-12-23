//
// Created by Chew Song Yu on 20/12/22.
//

#include "WebsocketServer.h"
#include "obj/Message/Message.h"
#include "obj/Parser/Parser.h"
#include <boost/asio.hpp>
#include <json/json.h>

using boost::asio::ip::tcp;

Json::Value WebsocketServer::parseJson(const std::string& jsonString) {
    Json::Value root;
    Json::Reader reader;
    bool success = reader.parse(jsonString, root);
    if (!success) {
        std::clog << "Json parse failed for " << jsonString << std::endl;
        // TODO: throw error and log failure somewhere
    }
    return root;
}

std::string WebsocketServer::stringifyJson(const Json::Value& json) {
    Json::StreamWriterBuilder wbuilder;
    wbuilder["commentStyle"] = "None";
    wbuilder["indentation"] = "";

    return Json::writeString(wbuilder, json);
}

std::function<void(Connection conn)> onOpenProducer(WebsocketServer* server) {
    return [server](Connection conn){

    };
}

std::function<void(Connection conn)> onCloseProducer(WebsocketServer* server) {
    return [server](Connection conn){

    };
}

std::function<void(Connection conn, WebsocketEndpoint::message_ptr)> onMessageProducer(WebsocketServer* server) {
    return [server](Connection conn, WebsocketEndpoint::message_ptr msg){
        std::cout << "on_message called with hdl: " << conn.lock().get()
                  << " and message: " << msg->get_payload()
                  << std::endl;

        Message* message = Parser::parseMessage(WebsocketServer::parseJson(msg->get_payload()));
        server->handleMessage(message);
        std::cout << "map: " << server->getMessagesMap() << std::endl;

        try {
            server->getEndpoint().send(conn, "Echo: " + msg->get_payload(), msg->get_opcode());
        } catch (const websocketpp::exception& e) {
            std::cout << "Echo failed because: "
                      << "(" << e.what() << ")" << std::endl;
        }
    };
}

WebsocketServer::WebsocketServer(): messagesMap{}, numConnections{ 0 } {

    //Initialise the Asio library, using our own event loop object
    endpoint.set_error_channels(websocketpp::log::elevel::all);
    endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

    // set handlers
    endpoint.set_open_handler(onOpenProducer(this));
    endpoint.set_close_handler(onCloseProducer(this));
    endpoint.set_message_handler(onMessageProducer(this));

    endpoint.init_asio(&(this->eventLoop));
}

void WebsocketServer::handleMessage(Message* message) {
    switch (message->getMessageType()) {
        case MessageType::REGISTER:
            // TODO: add to conn map
            break;
        case MessageType::UNREGISTER:
            // TODO: remove from conn map
            break;
        case MessageType::PUBLISH:
            messagesMap.push(message);
            std::cout << "message pushed" << std::endl;
            break;
    }
}

WebsocketServer::~WebsocketServer() {
    endpoint.stop_listening();
    endpoint.stop();
}

void WebsocketServer::run(int port) {
    if (running) {
        return ;
    }

    running = true;
    endpoint.listen(port);
    endpoint.start_accept();
    std::cout << "Server running on port " << port << std::endl;
    std::cout << "Waiting for connections..." << std::endl;
    endpoint.run();
}
