//
// Created by Chew Song Yu on 20/12/22.
//

#include "WebsocketServer.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

WebsocketServer::WebsocketServer() {
    //Initialise the Asio library, using our own event loop object
    this->endpoint.init_asio(&(this->eventLoop));
}

WebsocketServer::~WebsocketServer() {}

void WebsocketServer::run(int port) {
    if (running) {
        return ;
    }

    running = true;
    this->endpoint.listen(port);
    this->endpoint.start_accept();
    std::cout << "Server running on port " << port << std::endl;
    std::cout << "Waiting for connections..." << std::endl;
    this->endpoint.run();
}
