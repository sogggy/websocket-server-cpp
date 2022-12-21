//
// Created by Chew Song Yu on 20/12/22.
//

#include "WebsocketServer.h"
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

std::function<void(Connection conn)> onOpenProducer(WebsocketEndpoint& endpoint) {
    return [&endpoint](Connection conn){

    };
}

std::function<void(Connection conn)> onCloseProducer(WebsocketEndpoint& endpoint) {
    return [&endpoint](Connection conn){

    };
}

std::function<void(Connection conn, WebsocketEndpoint::message_ptr)> onMessageProducer(WebsocketEndpoint& endpoint) {
    return [&endpoint](Connection conn, WebsocketEndpoint::message_ptr msg){
        std::cout << "on_message called with hdl: " << conn.lock().get()
                  << " and message: " << msg->get_payload()
                  << std::endl;

        Json::Value root = WebsocketServer::parseJson(msg->get_payload());
        const Json::Value type = root["type"];
        // parse payload into message struct
        std::cout << "Payload type: " << type.asString() << std::endl;

        try {
            endpoint.send(conn, "Echo: " + msg->get_payload(), msg->get_opcode());
        } catch (websocketpp::exception const & e) {
            std::cout << "Echo failed because: "
                      << "(" << e.what() << ")" << std::endl;
        }
    };
}

WebsocketServer::WebsocketServer() {
    //Initialise the Asio library, using our own event loop object
    endpoint.set_error_channels(websocketpp::log::elevel::all);
    endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

    // set handlers
    endpoint.set_open_handler(onOpenProducer(endpoint));
    endpoint.set_close_handler(onCloseProducer(endpoint));
    endpoint.set_message_handler(onMessageProducer(endpoint));

    endpoint.init_asio(&(this->eventLoop));
}

WebsocketServer::~WebsocketServer() {}

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
