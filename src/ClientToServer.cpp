//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#include <ClientToServer.h>
#include <ConnectionHandler.h>

#include "ClientToServer.h"
#include <boost/algorithm/string.hpp>

using namespace std;


ClientToServer::ClientToServer(ConnectionHandler &connectionHandler) : connectionHandler(connectionHandler), toTerminate(false), toFinish(false) {
}


void ClientToServer::operator()() {
    while (!toTerminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        int len = line.length();
        vector<string> splitted;
        boost::split(splitted, line, ' ');
        char opCode[2];

        if (splitted[0] == "REGISTER"){
            string userName(splitted[1]);
            string password(splitted[2]);
            shortToBytes(1, opCode);
            short opc = 2;
            connectionHandler.sendBytes(opCode, 2);
            connectionHandler.sendLine(userName);
            connectionHandler.sendLine(password);

        }else if(splitted[0] == "LOGIN"){
            string userName(splitted[1]);
            string password(splitted[2]);
            shortToBytes(2, opCode);
            connectionHandler.sendBytes(opCode, 2);
            connectionHandler.sendLine(userName);
            connectionHandler.sendLine(password);

        }else if(splitted[0] == "LOGOUT"){
            shortToBytes(3, opCode);
            connectionHandler.sendBytes(opCode, 2);
            toTerminate = true;
        }
        else if (splitted[0] == "FOLLOW"){
            if (splitted.size() > 2) {
                string names = "";

                //sends the opCode
                shortToBytes(4, opCode);
                connectionHandler.sendBytes(opCode, 2);

                //sends the follow/unfollow
                string toFollow = splitted[1];
                char followCode[1];
                if (stoi(toFollow) == 0){
                    shortToBytes(0, followCode);
                    connectionHandler.sendBytes(followCode, 1);
                }
                else {
                    shortToBytes(1, followCode);
                    connectionHandler.sendBytes(followCode, 1);
                }

                //sends number of users
                string numOfUsers = splitted[2];
                int numOf = stoi(numOfUsers);
                short realNumOfUsers = (short) numOf;

                //sends all the names
                for (unsigned int i = 0; i < numOf; i++) {
                    connectionHandler.sendLine(splitted[3 + i]);
                }
            }
        }
        else if (splitted[0] == "POST"){
            string content = "";

            //checks if message is not empty
            if(splitted.size() > 1) {
                content = splitted[1];
            }
            for (unsigned int i = 2; i < splitted.size(); i++){
                content = content + " " + splitted[i];
            }
            shortToBytes(5, opCode);
            connectionHandler.sendBytes(opCode, 2);
            connectionHandler.sendLine(content);
        }

        else if (splitted[0] == "PM") {

            //checks if message is not empty
            if (splitted.size() > 1) {
                string userName = splitted[1];
                string content = "";
                if (splitted.size() > 2) {
                    content = splitted[2];
                }
                for (unsigned int i = 3; i < splitted.size(); i++) {
                    content = content + " " + splitted[i];
                }
                shortToBytes(6, opCode);
                connectionHandler.sendBytes(opCode, 2);
                connectionHandler.sendLine(userName);
                connectionHandler.sendLine(content);
            }
        }
        else if (splitted[0] == "USERLIST"){
            string all(opCode);
            shortToBytes(7, opCode);
            connectionHandler.sendBytes(opCode, 2);
        }
        else if (splitted[0] == "STAT"){
            if (splitted.size() == 2){
                string userName = splitted[1];
                shortToBytes(8, opCode);
                connectionHandler.sendBytes(opCode, 2);
                connectionHandler.sendLine(userName);
            }
        }
    }

    while (!toFinish){
        //maybe to set a lock that makes him wait..............
    }
}

void ClientToServer::shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void ClientToServer::setToFinish(bool toFinish) {
    ClientToServer::toFinish = toFinish;
}
