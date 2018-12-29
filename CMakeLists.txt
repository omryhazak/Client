cmake_minimum_required(VERSION 3.13)
project(Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Client
        include/connectionHandler.h
        src/connectionHandler.cpp
        src/echoClient.cpp src/serverToClient.cpp include/serverToClient.h src/clientToServer.cpp include/clientToServer.h)
