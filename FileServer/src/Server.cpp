#include "Server.hpp"


using namespace fts;

// Connect connects the client to the specific server
void FileServer::StartServer(int connections){
    createAndBindServerSocket();
    if (listen(sockfd, connections) < 0)
         throw new ServerException(SERVER_FAILED_TO_START_LISTENING);
    isRunning = true;
}

bool FileServer::Accept(){
    if(!isRunning){
        throw new ServerException(SERVER_NOT_RUNNING);
    }

    struct sockaddr_in client;
    int len = sizeof(client);
    connfd = accept(sockfd, (struct sockaddr*)&client, (socklen_t *) &len);
    
    while(isRunning) {
        struct ClientRequest clientRequest = handleClientRequest();

    }
    if (clientRequest.status != OK) {
        return false;
    }

    openFile(clientRequest.create && mode == WRITE); // && mode == WRITE ensures we only create file when writing to a file 
    process();
    return true;
}

int FileServer::GetFileSize() {
    if (!isRunning && mode == READ)
        throw new ServerException(SERVER_NOT_RUNNING);

    return fileSize;
}

void FileServer::Close(){
    if (!isRunning)
        throw new ServerException(SERVER_NOT_RUNNING);

    if (close(sockfd) < 0)
        throw new ServerException(FAILED_TO_CLOSE_SERVER_SOCKET);
    
    isRunning = false;
}