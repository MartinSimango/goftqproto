#include "Server.hpp"


using namespace fts;

// Connect connects the client to the specific server
void FileServer::StartServer(int connections){
    createAndBindServerSocket();
    if (listen(sockfd, connections) < 0)
         throw new ServerException(SERVER_FAILED_TO_START_LISTENING);
    isRunning = true;
}

void FileServer::Accept(){
    if(!isRunning){
        throw new ServerException(SERVER_NOT_RUNNING);
    }

    struct sockaddr_in client;
    int len = sizeof(client);
    connfd = accept(sockfd, (struct sockaddr*)&client, (socklen_t *) &len);
    
    if (connfd < 0) {
        throw new ServerException(FAILED_TO_ACCEPT_CONNECTION);
    }
    
}

int FileServer::GetFileSize() {
    if (!isRunning && mode == Mode::READ)
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

Response * FileServer::HandleClientRequest() {
    RequestHeader *header = new RequestHeader(connfd);
    header->Read();
    switch (header->requestType) {
    case RequestType::CREATE:
        CreateRequest *request = new CreateRequest(connfd, header);
        handleRequest(request);
        break;
    case RequestType::GET:
        GetRequest *request = new GetRequest(connfd, header);
        handleRequest(request);
        break;
    case RequestType::READ:
        ReadRequest *request = new ReadRequest(connfd, header);
        handleRequest(request);
        break;
    case RequestType::WRITE:
        WriteRequest *request = new WriteRequest(connfd, header);
        handleRequest(request);
        break;
    default:
        break;
    }

}
