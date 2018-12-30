//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#ifndef CLIENT_CLIENTTOSERVER_H
#define CLIENT_CLIENTTOSERVER_H


#include "ConnectionHandler.h"

class ClientToServer {
private:
    ConnectionHandler &connectionHandler;
    bool toTerminate;
    bool toFinish;

public:
    ClientToServer(ConnectionHandler &connectionHandler);    //constructor
    void operator()();
    void shortToBytes(short num, char* bytesArr);

    void setToFinish(bool toFinish);
};


#endif //CLIENT_CLIENTTOSERVER_H
