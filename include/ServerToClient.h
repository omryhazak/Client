//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#ifndef CLIENT_SERVERTOCLIENT_H
#define CLIENT_SERVERTOCLIENT_H

#include "ConnectionHandler.h"


class ServerToClient {
private:
    ConnectionHandler &connectionHandler;
    bool toTerminate;

public:
    ServerToClient(ConnectionHandler &connectionHandler);
    void operator()();
    short bytesToShort(char* bytesArr);
};


#endif //CLIENT_SERVERTOCLIENT_H
