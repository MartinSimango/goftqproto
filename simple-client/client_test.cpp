#include "Client.hpp"
#include <iostream>

using namespace ftc;
using namespace std;

int main(){

    struct ServerPort serverPort;

    serverPort.port = 3000;
    serverPort.serverAddress = "127.0.0.1";

    struct FilePacket filePacket;
    strcpy(filePacket.data, "Hello World!");
    strcpy(filePacket.filename, "File.txt");
    filePacket.offset = 0;
    filePacket.mode = WRITE;

    FileClient fileClient;

     cout << "File Packet: " << endl;
        cout << filePacket.data << endl;
        cout << filePacket.filename << endl;
        cout << filePacket.offset << endl;
        cout << filePacket.mode << endl;


    if(!fileClient.Connect(&serverPort)){
        cout << "Failed to connect to server!" <<endl;
        return -1;
    }
    cout << "Trying to write" << endl;
    cout << "OL"<<endl;
    if(fileClient.WriteToServer(&filePacket) == -1) {
        cout << "Failed to write to server" <<endl;
        return -1;
    }
    cout << "a " << endl;


    fileClient.Close();

    cout << "Program succeeded" << endl;
    return 0;

}
