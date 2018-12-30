//
// Created by omryh@wincs.cs.bgu.ac.il on 12/29/18.
//

#include "ServerToClient.h"
using namespace std;

ServerToClient::ServerToClient(ConnectionHandler &connectionHandler) : connectionHandler(connectionHandler), toTerminate(false) {

}

void ServerToClient::operator()() {
    while (!toTerminate){
        string message;

        char * opCode = new char[2];

        //gets opcode from user and converting it to short
        connectionHandler.getBytes(opCode, 2);
        short op = bytesToShort(opCode);

        string ans;
        //checks if it is a notification
        if (op == 9){
            ans = "NOTIFICATION";

            //gets PM or PUBLIC from user
            char * type = new char[1];
            connectionHandler.getBytes(type, 1);
            short t = bytesToShort(type);

            //checks which type of message is that
            if (t == 0){
                ans = ans + "PM";
            }
            else{
                ans = ans + " PUBLIC";
            }

            //takes chars until we get terminate zero in order to get all the name
            string name = "";
            connectionHandler.getFrameAscii(name, '\0');
            name = name.substr(0, name.size()-2);
            ans = ans + " name";

            //takes message content
            string content = "";
            connectionHandler.getFrameAscii(content, '\0');
            content = content.substr(0, name.size()-2);
            ans = ans + " " + content;

            cout << ans << endl;
    }

        else if(op == 10){
            ans = "ACK";

            char * opCode2 = new char[2];

            //gets opcode from user and converting it to short
            connectionHandler.getBytes(opCode2, 2);
            short op2 = bytesToShort(opCode2);
            ans = ans + " " + to_string(op2);

            //checks if it is special message we need to continue process
            if (op2 == 4 || op2 == 7){

                //gets num of users succeded following\unfollowing from user and converting it to short
                char * numOf = new char[2];
                connectionHandler.getBytes(numOf, 2);
                short numOfUsers = bytesToShort(numOf);
                ans = ans + " " + to_string(numOfUsers);

                int i = 0;
                while (i < numOfUsers){
                    string name;
                    connectionHandler.getFrameAscii(name, '\0');
                    name = name.substr(0, name.size()-2);
                    ans = ans + " " + name;
                }
                cout << ans << endl;
            }
            else if (op2 == 8) {
                //gets num of posts
                char *numOfP = new char[2];
                connectionHandler.getBytes(numOfP, 2);
                short numOfPosts = bytesToShort(numOfP);
                ans = ans + " " + to_string(numOfPosts);

                //gets num of followers
                char *numOfF = new char[2];
                connectionHandler.getBytes(numOfF, 2);
                short numOfFollowers = bytesToShort(numOfF);
                ans = ans + " " + to_string(numOfFollowers);

                //gets num of following
                char *numOfFo = new char[2];
                connectionHandler.getBytes(numOfFo, 2);
                short numOfFollowing = bytesToShort(numOfFo);
                ans = ans + " " + to_string(numOfFollowing);

                cout << ans << endl;
            }
            else if (op2 == 3){
                cout << ans << endl;
                toTerminate =   true;
            }
        }

        else if(op == 11){
            ans = "ERROR";

            //gets opcode from user and converting it to short
            char * opCode2 = new char[2];
            connectionHandler.getBytes(opCode2, 2);
            short op2 = bytesToShort(opCode2);
            ans = ans + " " + to_string(op2);

            cout << ans << endl;
        }
    }

}

short bytesToShort(char* bytesArr) {
    short result = (short)((bytesArr[0] & 0xff) << 8);
    result += (short)(bytesArr[1] & 0xff);
    return result;
}


