#include <Server.hpp>
#include <ServerWrapper.h>

using namespace fts;

FileServer* AsFileServer(void* fs) { 
    return reinterpret_cast<FileServer*>(fs); 
}

void* NewFileServer(int port, char * rootFoolder){
    auto fs = new FileServer(port, rootFoolder);
    return fs;
}

void DestroyFileServer(void* fs){
    AsFileServer(fs)->~FileServer();
}

void StartServer(void* fs, int connections){
    AsFileServer(fs)->StartServer(connections);
}

bool Accept(void* fs){
    return AsFileServer(fs)->Accept();
}

void CloseFileServer(void* fs){
    AsFileServer(fs)->Close();

}

const char * GetErrorMessage(void* fs){
    return AsFileServer(fs)->getErrorMessage();
}