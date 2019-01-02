cmake_minimum_required(VERSION 3.12)
project(Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(${Boost_INCLUDE_Dir})
link_directories(${Boost_LIBRARY_Dir})
find_package(Boost COMPONENTS system filesystem REQUIRED)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++11 -pthread -lboost_thread")

add_executable(Client
        include/ConnectionHandler.h
        src/ConnectionHandler.cpp
        src/ServerToClient.cpp include/ServerToClient.h src/ClientToServer.cpp include/ClientToServer.h src/Client.cpp)


target_link_libraries(Client ${Boost_LIBRARIES})