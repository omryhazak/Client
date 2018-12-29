//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#include <ClientToServer.h>
#include <ConnectionHandler.h>

#include "ClientToServer.h"
#include <boost/algorithm/string.hpp>

using namespace std;


ClientToServer::ClientToServer(ConnectionHandler &connectionHandler) : connectionHandler(connectionHandler) {

}


void ClientToServer::operator()() {
    while (1) {
        const short bufsize = 1024;
        char buf[bufsize];
        cin.getline(buf, bufsize);
        string line(buf);
        int len = line.length();
        vector<string> splitted;
        boost::split(splitted, line, ' ');
        if (splitted[0] == "REGISTER"){
            if (splitted.size() == 3) {
                string userName(splitted[1]);
                string password(splitted[2]);
                string all("1" + userName + '\0' + password + '\0');
                connectionHandler.sendLine(all);
            }
        }else if(splitted[0] == "LOGIN"){
            if (splitted.size() == 3) {
                string userName(splitted[1]);
                string password(splitted[2]);
                string all("2" + userName + '\0' + password + '\0');
                connectionHandler.sendLine(all);
            }
        }else if(splitted[0] == "LOGOUT"){
            string all = "3";
            connectionHandler.sendLine(all);
        }
        else if (splitted[0] == "FOLLOW"){
            if (splitted.size() > 2) {
                string toFollow = splitted[1];

                //maybe we need to check if number is actual number????????

                string numOfUsers = splitted[2];
                string names = "";
                for (unsigned int i = 0; i < stoi(numOfUsers); i++) {
                    names = names + "\0" + splitted[3 + i];
                }
                string all("4" + toFollow + '\0' + numOfUsers + names + "\0");
                connectionHandler.sendLine(all);
            }
        }
        else if (splitted[0] == "POST"){
            string content = "";
            if(splitted.size() > 1) {
                content = splitted[1];
            }
            for (unsigned int i = 2; i < splitted.size(); i++){
                content = content + " " + splitted[i];
            }
            string all("5" + '\0' + content + "\0");
            connectionHandler.sendLine(all);
        }
        else if (splitted[0] == "PM") {
            if (splitted.size() > 1) {
                string userName = splitted[1];
                string content = "";
                if (splitted.size() > 2) {
                    content = splitted[2];
                }
                for (unsigned int i = 3; i < splitted.size(); i++) {
                    content = content + " " + splitted[i];
                }
                string all("6" + '\0' + content + "\0");
                connectionHandler.sendLine(all);
            }
        }
        else if (splitted[0] == "USERLIST"){
            string all = "7";
            connectionHandler.sendLine(all);
        }
        else if (splitted[0] == "STAT"){
            if (splitted.size() == 2){
                string userName = splitted[1];
                string all = userName + "\0";
                connectionHandler.sendLine(all);
            }
        }
    }
}