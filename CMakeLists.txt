cmake_minimum_required(VERSION 3.13)
project(Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Client
        include/ConnectionHandler.h
        src/ConnectionHandler.cpp
        src/ServerToClient.cpp include/ServerToClient.h src/ClientToServer.cpp include/ClientToServer.h src/Client.cpp)
