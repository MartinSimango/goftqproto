#include <Server.hpp>
#include <ServerWrapper.h>

using namespace fts;

FileServer* AsFileServer(void* fs) { 
    return reinterpret_cast<FileServer*>(fs); 
}

void* NewFileServer(int port){
    auto fs = new FileServer(port);
    return fs;
}

void DestroyFileServer(void* fs){
    AsFileServer(fs)->~FileServer();
}

bool StartServer(void* fs, int connections){
    return AsFileServer(fs)->StartServer(connections);
}

bool Accept(void* fs){
    return AsFileServer(fs)->Accept();
}

bool Close(void* fs){
    return AsFileServer(fs)->Close();

}

const char * GetErrorMessage(void* fs){
    return AsFileServer(fs)->getErrorMessage();
}