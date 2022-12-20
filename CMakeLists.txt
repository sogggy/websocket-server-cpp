cmake_minimum_required(VERSION 3.24)
project(websocket_server_cpp)

set(CMAKE_CXX_STANDARD 17)
set(Boost_INCLUDE_DIRS /opt/homebrew/Cellar/boost/1.80.0/include)
set(Websocketpp_INCLUDE_DIRS /opt/homebrew/Cellar/websocketpp/0.8.2/include)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${Websocketpp_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(src)

add_executable(websocket_server_cpp main.cpp src/WebsocketServer/WebsocketServer.h src/constants/constants.h src/WebsocketServer/WebSocketServer.cpp)
