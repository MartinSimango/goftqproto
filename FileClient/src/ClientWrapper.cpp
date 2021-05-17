
#include <ClientWrapper.h>
#include <Client.hpp>
#include <ErrorVoid.hpp>
#include <iostream>

using namespace ftc;

FileClient* AsFileClient(void* fc) { 
    return reinterpret_cast<FileClient*>(fc); 
}


void* NewFileClient() {
    FileClient * fc = new FileClient();
    return fc;
}

void DestroyFileClient(void* fc){
    AsFileClient(fc)->~FileClient();
}

// Connect connects the client to the specific server specified by the ServerPort 
// returns false if connect failed and errorMessage is set
void * Connect(void* fc, char * serverAddress, int port) {
    struct ServerPort serverPort;
    serverPort.port = port;
    strncpy(serverPort.serverAddress, serverAddress, sizeof(serverPort.serverAddress));
    Error<void, FileClient,ServerPort> * error = new Error<void, FileClient, ServerPort>(&FileClient::Connect, AsFileClient(fc));
    error->Execute(serverPort);
    return dynamic_cast<ErrorBase*>(error);
}

void * SendCreateRequest(void* fc, char * filenames[], int fileSizes[], int numFiles){
    std::vector<request::File> * files = new std::vector<request::File>(numFiles);
    for(int i=0; i< numFiles; i++){
        files->at(i).setFileName(filenames[i]);
        files->at(i).fileSize = fileSizes[i];
    }

    Error<CreateResponseStruct, FileClient, std::vector<request::File>* > * error = new Error<CreateResponseStruct, FileClient, std::vector<request::File>*>(&FileClient::SendCreateRequest, AsFileClient(fc));
    error->Execute(files);
    return dynamic_cast<ErrorBase*>(error);

}

void * SendGetRequest(void* fc, char * filepath) {
    Error<GetResponse, FileClient, char *> * error = new Error<GetResponse, FileClient, char *>(&FileClient::SendGetRequest, AsFileClient(fc));
    error->Execute(filepath);
    return dynamic_cast<ErrorBase*>(error);
}

void * SendReadRequest(void* fc, int numberOfBytesToRead, int offset, char *readFile, char * writeFile){
    Error<ReadResponse, FileClient, int,int,char *, char*> * error = new Error<ReadResponse, FileClient,int,int, char *, char*>(&FileClient::SendReadRequest, AsFileClient(fc));
    error->Execute(numberOfBytesToRead, offset, readFile, writeFile);

    return dynamic_cast<ErrorBase*>(error);
}

void * SendWriteRequest(void* fc, int numberOfBytesToWrite, int offset, char *readFile, char * writeFile){
    Error<WriteResponse, FileClient, int,int,char *, char*> * error = new Error<WriteResponse, FileClient,int,int, char *, char*>(&FileClient::SendWriteRequest, AsFileClient(fc));
    error->Execute(numberOfBytesToWrite, offset, readFile, writeFile);

    return dynamic_cast<ErrorBase*>(error);
}


// CloseFileClient closes the connection to the server, returns false upon failure
void * CloseFileClient(void* fc){
    Error<void, FileClient> * error = new Error<void, FileClient>(&FileClient::Close, AsFileClient(fc)); 
    error->Execute();

    return dynamic_cast<ErrorBase*>(error);
}


