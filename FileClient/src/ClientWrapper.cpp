
#include <ClientWrapper.h>
#include <Client.hpp>
#include <ErrorVoid.hpp>

using namespace ftc;

FileClient* AsFileClient(void* fc) { 
    return reinterpret_cast<FileClient*>(fc); 
}


void* NewFileClient(int mode, char * requestFileName, char * filename) {
    FileClient * fc = new FileClient(mode, requestFileName, filename);
    return fc;
}

void DestroyFileClient(void* fc){
    AsFileClient(fc)->~FileClient();
}

// Connect connects the client to the specific server specified by the ServerPort 
// returns false if connect failed and errorMessage is set
void * Connect(void* fc, char * serverAddress, int port, bool create) {
    struct ServerPort serverPort;
    serverPort.port = port;
    strncpy(serverPort.serverAddress, serverAddress, sizeof(serverPort.serverAddress));
    
    Error<void,FileClient,ServerPort, bool> * error = new Error<void, FileClient, ServerPort, bool>(&FileClient::Connect, AsFileClient(fc));

    try {
        error->Execute(serverPort, create);
    }
    catch(fce::FileCopierException* e) {
        error->SetErrorMessage(&fce::FileCopierException::getErrorMessage, e);
        delete e;
    }
    return dynamic_cast<ErrorBase*>(error);

}



// Process either reads or writes to the server depending on what mode the FileClient is in
// returns the number of bits written or read to the server depending on the mode
void* Process(void* fc, int offset, int numberOfBytesRead){
    Error<int, FileClient, int, int> * error = new Error<int, FileClient, int, int>(&FileClient::Process, AsFileClient(fc));
    
    try {
         error->Execute(offset, numberOfBytesRead);
    }
    catch(fce::FileCopierException* e) {
        error->SetErrorMessage(&fce::FileCopierException::getErrorMessage, e);
        delete e;
    }
    return dynamic_cast<ErrorBase*>(error);
}

void * GetFileClientFileSize(void *fc) {
    Error<int, FileClient> * error = new Error<int, FileClient>(&FileClient::GetFileSize, AsFileClient(fc));
    try {
        error->Execute();
    }
    catch(fce::FileCopierException* e) {
        error->SetErrorMessage(&fce::FileCopierException::getErrorMessage, e);
        delete e;
    }

    return dynamic_cast<ErrorBase*>(error);
}

// CloseFileClient closes the connection to the server, returns false upon failure
void * CloseFileClient(void* fc){
    Error<void, FileClient> * error = new Error<void, FileClient>(&FileClient::Close, AsFileClient(fc));
    try {
        error->Execute();
    }
    catch(fce::FileCopierException* e) {
        error->SetErrorMessage(&fce::FileCopierException::getErrorMessage, e);
        delete e;
    }

    return dynamic_cast<ErrorBase*>(error);
}


