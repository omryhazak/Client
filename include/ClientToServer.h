//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#ifndef CLIENT_CLIENTTOSERVER_H
#define CLIENT_CLIENTTOSERVER_H


#include "ConnectionHandler.h"

class ClientToServer {
private:
    ConnectionHandler connectionHandler;
public:
    ClientToServer(ConnectionHandler &connectionHandler);

    void operator()();

};


#endif //CLIENT_CLIENTTOSERVER_H
