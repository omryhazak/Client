//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#ifndef CLIENT_CLIENTTOSERVER_H
#define CLIENT_CLIENTTOSERVER_H


#include "ConnectionHandler.h"
#include "ConnectionHandler.h"
#include <mutex>
#include <condition_variable>

using namespace std;

class ClientToServer {
private:
    ConnectionHandler *connectionHandler;
    bool toTerminate;
    mutex &mutex1;
    condition_variable &cv;

public:
    ClientToServer(ConnectionHandler *connectionHandler,condition_variable &cv ,mutex &mutex1);    //constructor
    void run();
    void shortToBytes(short num, char* bytesArr);
    void setToTerminate(bool toTerminate);
};


#endif //CLIENT_CLIENTTOSERVER_H
