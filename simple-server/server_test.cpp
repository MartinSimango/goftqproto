#include "Server.hpp"
#include <iostream>

using namespace fts;
using namespace std;

int main(){

    
    FileServer fileServer(3000);

    if(!fileServer.StartServer(5)){
        cout << "Failed to start server" <<endl;
        return -1;
    }
    
    if(!fileServer.Accept()){
        cout << "Failed to read from client" <<endl;
        return -1;
    }

    fileServer.Close();

    cout << "Program succeeded" << endl;
    return 0;

}