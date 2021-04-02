#include "Client.hpp"
#include <iostream>

using namespace fileClient;
using namespace std;

int main(){

    struct ServerPort serverPort;

    serverPort.port = 3000;
    serverPort.serverAddress = "127.0.0.1";

    struct FilePacket filePacket;
    strcpy(filePacket.data, "Hello World!");
    strcpy(filePacket.filename, "File.txt");
    filePacket.offset = 122;
    filePacket.messageType = READ;

    FileClient fileClient(&serverPort);

     cout << "File Packet: " << endl;
        cout << filePacket.data << endl;
        cout << filePacket.filename << endl;
        cout << filePacket.offset << endl;
        cout << filePacket.messageType << endl;


    if(!fileClient.Connect()){
        cout << "Failwd to connect to server!" <<endl;
        return -1;
    }
    
    if(fileClient.WriteToServer(&filePacket) == -1) {
        cout << "Failed to write to server!" <<endl;
        return -1;
    }


    fileClient.Close();

    cout << "Program succeeded" << endl;
    return 0;

}
