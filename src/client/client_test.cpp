#include <iostream>
#include <Client.hpp>

using namespace ftc;
using namespace std;

int main(){

    struct ServerPort serverPort;

    serverPort.port = 3000;
    serverPort.serverAddress = "127.0.0.1";

    FileClient fileClient(WRITE, "test.txt", "File.txt");
    if (!fileClient.Connect(serverPort)){
        cout << "Failed to connect to server" << endl;
        exit(1);
    }

    if(fileClient.Process(2,10) < 0){
        cout << "Failed to process to server" << endl;
        exit(1);
    }
    if (!fileClient.Close()) {
        cout << "Failed to close connection" << endl;
        exit(1);
    }

    cout << "Program done " << endl; 
    return 0;

}
