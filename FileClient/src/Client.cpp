#include <Client.hpp>

using namespace ftc;


void FileClient::Connect(struct ServerPort serverPort) {
    if (isConnected)
        throw new ClientException(CLIENT_ALREADY_CONNECTED);
    
    connectToServer(serverPort);
    isConnected = true;
}



void FileClient::SendGetRequest(char * filepath){
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);

    GetRequest request(sockfd, filepath);
    request.WriteRequest();
    
    //read response from server
}

void FileClient::SendCreateRequest(std::vector<request::File> * files) {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);

    CreateRequest createRequest(sockfd, files);
    createRequest.WriteRequest();
    //read response from server

}
void FileClient::SendReadRequest(int numberOfBytesToRead, int offset, char *readFile, char * writeFile) {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);
    
    ReadRequest readRequest(sockfd, readFile, offset, numberOfBytesToRead);
    readRequest.WriteRequest();

}

void FileClient::SendWriteRequest(int numberOfBytesToWrite, int offset, char *readFile, char * writeFile) {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);
    FileReadWriter * frw = new FileReadWriter(readFile, Mode::READ);
    frw->Open();
    
    int bytes_written = writeToServer(frw, writeFile, numberOfBytesToWrite, offset);
    frw->Close();
    delete frw;

    //read response from server    
}


void FileClient::ReadResponse(Request * request) {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);
    switch (request->GetPacketType())
    {
    case ResponseType::CREATE:
        break;
    case ResponseType::GET:
        break;
    case ResponseType::READ:
        break;
    case ResponseType::WRITE:
        break;
    
    default:
        break;
    }
}


int FileClient::Process(int offset, int numberOfBytesRead){
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);
        
    FileConfigPacket request(sockfd, offset, numberOfBytesRead);

    return (mode == READ) ? readFromServer(&request): writeToServer(&request);
}

int FileClient::GetFileSize() {
    if (!isConnected && mode == READ)
        throw new ClientException(CLIENT_NOT_CONNECTED);
        
    return fileSize;
}


void FileClient::Close() {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);
    if (close(sockfd) < 0) 
        throw new ClientException(FAILED_TO_CLOSE_CLIENT_SOCKET);

    isConnected = false;
}