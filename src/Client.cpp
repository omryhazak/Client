//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#include <stdlib.h>
#include <ConnectionHandler.h>
#include <ClientToServer.h>
#include <ServerToClient.h>
#include <thread>

using namespace std;

/**
* This code assumes that the server replies the exact text the client sent it (as opposed to the practical session example)
*/
int main (int argc, char *argv[]) {
    //gets host and port
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);

    //creats connection handler to talk through, we will later send to clientToServer and serverToClient
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    ClientToServer * clientToServer = new ClientToServer(connectionHandler);

    ServerToClient * serverToClient = new ServerToClient(connectionHandler);

    serverToClient->operator()();

    thread Th1(clientToServer);


    return 0;
    }
}