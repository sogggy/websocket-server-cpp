//
// Created by Chew Song Yu on 20/12/22.
//

#include <json/json.h>
#include "WebsocketServer.h"
#include "obj/Message/Message.h"
#include "obj/Parser/Parser.h"

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
        server->handleMessage(message, conn);
        std::cout << "map: " << server->getMessagesMap() << std::endl;

        try {
            server->getEndpoint().send(conn, "Echo: " + msg->get_payload(), msg->get_opcode());
        } catch (const websocketpp::exception& e) {
            std::cout << "Echo failed because: "
                      << "(" << e.what() << ")" << std::endl;
        }
    };
}

WebsocketServer::WebsocketServer(): connMap{}, messagesMap{}, numConnections{ 0 } {

    //Initialise the Asio library, using our own event loop object
    endpoint.set_error_channels(websocketpp::log::elevel::all);
    endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

    // set handlers
    endpoint.set_open_handler(onOpenProducer(this));
    endpoint.set_close_handler(onCloseProducer(this));
    endpoint.set_message_handler(onMessageProducer(this));

    endpoint.init_asio(&(this->eventLoop));
}

void WebsocketServer::handleMessage(Message* message, Connection conn) {
    switch (message->getMessageType()) {
        case MessageType::REGISTER:
            connMap.push_safe(message->getId(), conn);
            std::cout << "conn registered!" << std::endl;
            std::cout << "connMap: " << connMap << std::endl;
            break;
        case MessageType::UNREGISTER:
            std::cout << "conn unregistered!" << std::endl;
            std::cout << "connMap: " << connMap << std::endl;
            connMap.remove_safe(message->getId(), conn);
            break;
        case MessageType::PUBLISH:
            std::cout << "message published!" << std::endl;
            std::cout << "messageMap: " << messagesMap << std::endl;
            messagesMap.push(message);
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
