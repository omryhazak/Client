//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#include <ClientToServer.h>
#include <ConnectionHandler.h>

#include "ClientToServer.h"
#include <boost/algorithm/string.hpp>

using namespace std;


ClientToServer::ClientToServer(ConnectionHandler *connectionHandler, condition_variable &cv ,mutex &mutex) : connectionHandler(connectionHandler), toTerminate(false), cv(cv) ,mutex1(mutex) {
}


void ClientToServer::run() {
    while (!toTerminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        int len = line.length();
        vector<string> splitted;

        boost::split(splitted, line, boost::is_any_of(" "));

        char opCode[2];

        if (splitted[0] == "REGISTER"){
            string userName(splitted[1]);
            string password(splitted[2]);
            shortToBytes(1, opCode);

            connectionHandler->sendBytes(opCode, 2);
            connectionHandler->sendLine(userName);
            connectionHandler->sendLine(password);

        }else if(splitted[0] == "LOGIN"){
            string userName(splitted[1]);
            string password(splitted[2]);
            shortToBytes(2, opCode);
            connectionHandler->sendBytes(opCode, 2);
            connectionHandler->sendLine(userName);
            connectionHandler->sendLine(password);

        }else if(splitted[0] == "LOGOUT") {
            shortToBytes(3, opCode);
            connectionHandler->sendBytes(opCode, 2);

            unique_lock<mutex> lock{mutex1};
            cv.wait(lock);
        }
        else if (splitted[0] == "FOLLOW"){
            if (splitted.size() > 2) {
                string names = "";

                //sends the opCode
                shortToBytes(4, opCode);
                connectionHandler->sendBytes(opCode, 2);

                //sends the follow/unfollow
                string toFollow = splitted[1];
                char followCode[1];
                if (stoi(toFollow) == 0){
                    followCode[0] = static_cast<char> (0);
                    connectionHandler->sendBytes(followCode, 1);
                }
                else {
                    followCode[0] = static_cast<char> (1);
                    connectionHandler->sendBytes(followCode, 1);
                }

                //sends number of users
                string numOfUsers = splitted[2];
                //assigning the string to short
                int numOf = stoi(numOfUsers);
                short realNumOfUsers = (short) numOf;

                //assigning the short to bytes and sends it
                char number[1];
                shortToBytes(realNumOfUsers, number);
                connectionHandler->sendBytes(number, 2);

                //sends all the names
                for (unsigned int i = 0; i < numOf; i++) {
                    connectionHandler->sendLine(splitted[3 + i]);
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
            connectionHandler->sendBytes(opCode, 2);
            connectionHandler->sendLine(content);
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
                connectionHandler->sendBytes(opCode, 2);
                connectionHandler->sendLine(userName);
                connectionHandler->sendLine(content);
            }
        }
        else if (splitted[0] == "USERLIST"){
            string all(opCode);
            shortToBytes(7, opCode);
            connectionHandler->sendBytes(opCode, 2);
        }
        else if (splitted[0] == "STAT"){
            if (splitted.size() == 2){
                string userName = splitted[1];
                shortToBytes(8, opCode);
                connectionHandler->sendBytes(opCode, 2);
                connectionHandler->sendLine(userName);
            }
        }
    }
}

void ClientToServer::shortToBytes(short num, char* bytesArr) {
    bytesArr[0] = ((num >> 8) & 0xFF);
    bytesArr[1] = (num & 0xFF);
}

void ClientToServer::setToTerminate(bool toTerminate) {
    ClientToServer::toTerminate = toTerminate;
}
