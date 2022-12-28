//
// Created by Chew Song Yu on 28/12/22.
//

#include "obj/SafeQueue/SafeQueue.h"
#include "obj/SafeQueue/SafeQueue.cpp"
#include "obj/Message/Message.h"

template class SafeQueue<std::string>;
template class SafeQueue<Message>;
