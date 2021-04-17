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
    
    return handleClientRequest() && openFile() && process();
}

bool FileServer::Close(){
    if (isRunning) {
        if (close(sockfd) < 0) {
            errorMessage = FAILED_TO_CLOSE_SOCKET;
            return false;
        }
        isRunning = false;
        return true;
    }
    errorMessage = SERVER_NOT_RUNNING;
    return false;
    
}