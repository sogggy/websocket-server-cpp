//
// Created by Chew Song Yu on 20/12/22.
//

#include "WebsocketServer.h"

using boost::asio::ip::tcp;

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
        const std::string& payload = msg->get_payload();
        std::cout << "message: " << payload << "received" << std::endl;

        std::unique_ptr<Message> message = Parser::parseMessage(Parser::parseJsonString(payload));
        server->handleMessage(std::move(message), conn);
    };
}

WebsocketServer::WebsocketServer(): connMap{ &endpoint } {
    //Initialise the Asio library, using our own event loop object
    endpoint.set_error_channels(websocketpp::log::elevel::all);
    endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

    // set handlers
    endpoint.set_open_handler(onOpenProducer(this));
    endpoint.set_close_handler(onCloseProducer(this));
    endpoint.set_message_handler(onMessageProducer(this));

    endpoint.init_asio(&(this->eventLoop));
}

void WebsocketServer::handleMessage(std::unique_ptr<Message> message, Connection conn) {
    switch (message->getMessageType()) {
        case MessageType::REGISTER: {
            std::cout << "conn registered!" << std::endl;
            connMap.push_safe(message->getId(), conn);
            std::cout << "connMap: " << connMap << std::endl;
            break;
        }
        case MessageType::UNREGISTER: {
            std::cout << "conn unregistered!" << std::endl;
            connMap.remove_safe(message->getId(), conn);
            std::cout << "connMap: " << connMap << std::endl;
            break;
        }
        case MessageType::PUBLISH: {
            std::cout << "publish message received!" << std::endl;
            std::string id = message->getId();
            messagesMap.push(std::move(message));
            std::unique_lock<std::mutex> ul(mutex);
            jobsCount++;
            jobs.push_back_safe(std::make_unique<std::string>(id));
            cv.notify_one();
            ul.unlock();
            std::cout << "messageMap: " << messagesMap << std::endl;
            break;
        }
        default: {
            std::cout << "unrecognized message type!" << std::endl;
            break;
        }
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
