//
// Created by Chew Song Yu on 23/12/22.
//

#ifndef WEBSOCKET_SERVER_CPP_UNREGISTERMESSAGE_H
#define WEBSOCKET_SERVER_CPP_UNREGISTERMESSAGE_H

#include <json/json.h>

#include "Message.h"
#include "constants/messageTypes.h"

class UnregisterMessage: public Message {
private:
    explicit UnregisterMessage(const Json::Value& json);

public:
    UnregisterMessage() = delete;
    UnregisterMessage& operator=(Json::Value json);
    static UnregisterMessage* createMessage(const Json::Value& json);
    Json::Value toJson() override;

protected:
    void print(std::ostream& out) const override;
};


#endif //WEBSOCKET_SERVER_CPP_UNREGISTERMESSAGE_H
