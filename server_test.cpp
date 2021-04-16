#include <Server.hpp>
#include <iostream>

using namespace fts;
using namespace std;

int main(){

    
    FileServer fileServer(3000);
    if(!fileServer.StartServer(5)){
        cout << "Failed to start server" <<endl;
        return -1;
    }
    cout << "Server started..." << endl;

    
    if(!fileServer.Accept()){
        cout << "Failed to read from client" <<endl;
        cout << fileServer.getErrorMessage() << endl;
        return -1;
    }
    cout << "Closing server" <<endl;
    
    if(!fileServer.Close()) {
        cout << "Failed to close" <<endl;
    }

    cout << "Program succeeded" << endl;
    return 0;
}