#include "src/obj/WebsocketServer/WebsocketServer.h"
#include "src/constants/constants.h"

int main() {
    // TODO: spawn new websocket server instance,
    //  register network callbacks,
    //  spawn networking thread,
    //  spawn consumer worker thread

    WebsocketServer server;
    server.run(constants::PORT);
}
