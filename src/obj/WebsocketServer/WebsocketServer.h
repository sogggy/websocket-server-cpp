//
// Created by Chew Song Yu on 20/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
#define WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H

#include <condition_variable>
#include <string>
#include <mutex>

#include <boost/asio.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <json/value.h>

#include "obj/ConnMap/ConnMap.h"
#include "obj/Message/Message.h"
#include "obj/MessagesMap/MessagesMap.h"
#include "obj/Parser/Parser.h"

#include "types/types.h"

class WebsocketServer {
private:
    bool running{ false };
    ConnMap connMap;
    MessagesMap messagesMap;
    Jobs jobs;
    std::condition_variable cv;
    std::mutex mutex;

    std::function<void(Connection conn)> onOpen;
    std::function<void(Connection conn)> onClose;
    std::function<void(Connection conn, WebsocketEndpoint::message_ptr msg)> onMessage;

    WebsocketEndpoint endpoint;
    websocketpp::lib::asio::io_service eventLoop;

public:
    int jobsCount{};
    WebsocketServer();
    ~WebsocketServer();
    WebsocketServer(const WebsocketServer& server) = delete;
    WebsocketServer& operator=(const WebsocketServer& server) = delete;

    WebsocketEndpoint& getEndpoint() { return endpoint; }
    MessagesMap& getMessagesMap() { return messagesMap; }
    ConnMap& getConnMap() { return connMap; }
    Jobs& getJobs() { return jobs; }
    int getJobsCount() { return jobsCount; }
    std::condition_variable& getCv() { return cv; }
    std::mutex& getMutex() { return mutex; }

    void handleMessage(Message* message, Connection conn);

    void run(int port);
};

#endif //WEBSOCKET_SERVER_CPP_WEBSOCKETSERVER_H
