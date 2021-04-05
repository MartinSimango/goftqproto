#include "Server.hpp"


using namespace fts;

// Connect connects the client to the specific server
bool FileServer::StartServer(int connections){
    return isRunning = createServer() && !listen(sockfd, connections);
}

bool FileServer::Accept(){
    if(!isRunning){
        errorMessage = SERVER_NOT_RUNNING;
        return false;
    }

    struct sockaddr_in client;
    int len = sizeof(client);
    connfd = accept(sockfd, (struct sockaddr*)&client, (socklen_t *) &len);
    
    handleClientRequst();
}