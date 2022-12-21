cmake_minimum_required(VERSION 3.24)
project(websocket_server_cpp)

set(CMAKE_CXX_STANDARD 17)
set(Boost_INCLUDE_DIRS /opt/homebrew/Cellar/boost/1.80.0/include)
set(Websocketpp_INCLUDE_DIRS /opt/homebrew/Cellar/websocketpp/0.8.2/include)
set(Jsoncpp_INCLUDE_DIRS /opt/homebrew/Cellar/jsoncpp/1.9.5/include)
set(Jsoncpp_LIBRARIES /opt/homebrew/Cellar/jsoncpp/1.9.5/lib/*.dylib)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Websocketpp_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Jsoncpp_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(src)

LINK_DIRECTORIES(${Jsoncpp_INCLUDE_DIRS})

file(GLOB LIBRARIES ${Jsoncpp_LIBRARIES})
message("LIBRARIES = ${LIBRARIES}")

add_executable(websocket_server_cpp main.cpp src/obj/WebsocketServer/WebsocketServer.h src/constants/constants.h src/obj/WebsocketServer/WebSocketServer.cpp src/obj/Message/Message.h src/obj/Message/UpdateCellMessage.cpp src/obj/Message/UpdateCellMessage.h src/constants/messageTypes.h src/obj/Message/Message.cpp src/obj/Parser/Parser.h)
TARGET_LINK_LIBRARIES(websocket_server_cpp ${LIBRARIES})
