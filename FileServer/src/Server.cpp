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

void FileServer::Close(){
    if(!isRunning)
        throw new ServerException(SERVER_NOT_RUNNING);
    if (close(connfd) < 0) 
        throw new ServerException(FAILED_TO_CLOSE_CLIENT_SOCKET);
    if (close(sockfd) < 0)
        throw new ServerException(FAILED_TO_CLOSE_SERVER_SOCKET);
    
    isRunning = false;
}

bool FileServer::HandleClientRequest() {
    if(!isRunning){
        throw new ServerException(SERVER_NOT_RUNNING);
    }
    RequestHeader *header = new RequestHeader(connfd);
    if (header->Read() == 0) { //read nothing from the client then close the connection with it
         return false;
    }
    switch (header->requestType) {
        case RequestType::CREATE: {
            CreateRequest *request = new CreateRequest(connfd, header);
            request->ReadBody();
            handleRequest(request);
            delete request;
            break;
        }
        case RequestType::GET: {
            GetRequest *request = new GetRequest(connfd, header);
            request->ReadBody();
            handleRequest(request);
            delete request;
            break;
        }
        case RequestType::READ: {
            ReadRequest *request = new ReadRequest(connfd, header);
            request->ReadBody();
            handleRequest(request);
            delete request;
            break;
        }
        case RequestType::WRITE: {
            WriteRequest *request = new WriteRequest(connfd, header);
            request->ReadBody();
            handleRequest(request);
            delete request;
            break;
        }
        default: {//unknown request close connection
            return false;
            //todo log unknown request
        }
    }
    return true;

}

bool FileServer::IsServerRunning() {
    return isRunning;
}

