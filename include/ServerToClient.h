//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#ifndef CLIENT_SERVERTOCLIENT_H
#define CLIENT_SERVERTOCLIENT_H

#include <mutex>
#include <condition_variable>
#include "ConnectionHandler.h"

using namespace std;

class ServerToClient {
private:
    ConnectionHandler *connectionHandler;
    bool toTerminate;
    mutex &mutex1;
    condition_variable &cv;

public:
    ServerToClient(ConnectionHandler *connectionHandler,condition_variable &cv ,mutex &mutex1);
    void run();
    short bytesToShort(char* bytesArr);

};


#endif //CLIENT_SERVERTOCLIENT_H
