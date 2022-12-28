#include <string>
#include <mutex>

#include "src/obj/WebsocketServer/WebsocketServer.h"
#include "src/constants/constants.h"

int main() {
    // TODO: spawn new websocket server instance,
    //  register network callbacks,
    //  spawn networking thread,
    //  spawn consumer worker thread

    WebsocketServer server;

    std::thread workerThread([&]() {
        while (true) {
            std::unique_lock<std::mutex> ul(server.getMutex());
            server.getCv().wait(ul, [&]() {
                return server.getJobsCount() != 0;
            });
            const std::string id = *server.getJobs().pop_front_safe();
            server.jobsCount--;
            Message* message = server.getMessagesMap().getMessage(id);
            server.getConnMap().publish(id, message);
            ul.unlock();
        }
    });

    server.run(constants::PORT);
}
