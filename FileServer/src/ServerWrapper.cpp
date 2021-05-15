#include <Server.hpp>
#include <ServerWrapper.h>
#include <ErrorVoid.hpp>

using namespace fts;

FileServer* AsFileServer(void* fs) { 
    return reinterpret_cast<FileServer*>(fs); 
}

void* NewFileServer(int port, char * rootFoolder){
    FileServer * fs = new FileServer(port, rootFoolder);
    return fs;
}

void DestroyFileServer(void* fs){
    AsFileServer(fs)->~FileServer();
}

void* StartServer(void* fs, int connections){
    Error<void, FileServer, int> * error = new Error<void, FileServer,int>(&FileServer::StartServer, AsFileServer(fs));
    error->Execute(connections);
    return dynamic_cast<ErrorBase*>(error);
}

void* Accept(void* fs){
    Error<void, FileServer> * error = new Error<void, FileServer>(&FileServer::Accept, AsFileServer(fs));
    error->Execute();
    return dynamic_cast<ErrorBase*>(error);
}

void* HandleClientRequest(void * fs) {
    Error<bool, FileServer> * error = new Error<bool, FileServer>(&FileServer::HandleClientRequest, AsFileServer(fs));
    error->Execute();
    return dynamic_cast<ErrorBase*>(error);
}

void * IsServerRunning(void * fs) {
    Error<bool, FileServer> * error = new Error<bool, FileServer>(&FileServer::IsServerRunning, AsFileServer(fs));
    error->Execute();
    return dynamic_cast<ErrorBase*>(error);
}



void* CloseFileServer(void* fs){
    Error<void, FileServer> * error = new Error<void, FileServer>(&FileServer::Close, AsFileServer(fs));
    error->Execute();
    return dynamic_cast<ErrorBase*>(error);
}
