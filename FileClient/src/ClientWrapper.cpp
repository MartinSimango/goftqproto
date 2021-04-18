
#include <ClientWrapper.h>
#include <Client.hpp>
#include <iostream>
using namespace ftc;

FileClient* AsFileClient(void* fc) { 
    return reinterpret_cast<FileClient*>(fc); 
}

void* NewFileClient(int mode, char * requestFileName, char * filename = (char*)0) {
    auto fc = new FileClient(mode, requestFileName, filename);
    return fc;
}

void DestroyFileClient(void* fc){
    AsFileClient(fc)->~FileClient();
}

// Utility function local to the bridge's implementation

// Connect connects the client to the specific server specified by the ServerPort 
// returns false if connect failed and errorMessage is set
bool Connect(void* fc, char * serverAddress, int port){
    struct ServerPort serverPort;
    serverPort.port = port;
    strncpy(serverPort.serverAddress, serverAddress, sizeof(serverPort.serverAddress)); //todo: use strlcpy or strncpy
    return AsFileClient(fc)->Connect(serverPort);
}
// Process either reads or writes to the server depending on what mode the FileClient is in
// returns the number of bits written or read to the server depending on the mode
int Process(void* fc, int offset, int numberOfBytesRead){
    return AsFileClient(fc)->Process(offset, numberOfBytesRead);
}
// GetErrorMessge returns the errorMessage 
const char * GetErrorMessage(void* fc){
    return AsFileClient(fc)->GetErrorMessage();
}
// Close closes the connection to the server, returns false upon failure
bool Close(void* fc){
    return AsFileClient(fc)->Close();
}