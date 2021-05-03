#include <Client.hpp>

using namespace ftc;


void FileClient::Connect(struct ServerPort serverPort, bool create){
    if (isConnected)
        throw new ClientException(CLIENT_ALREADY_CONNECTED);
    
    connectToServer(serverPort);
    requestToServer(create && mode == WRITE);
    openFile(create && mode == READ);
    isConnected = true;
}

int FileClient::Process(int offset, int numberOfBytesRead){
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);
        
    FileConfigPacket packet(sockfd, offset, numberOfBytesRead);

    return (mode == READ) ? readFromServer(&packet): writeToServer(&packet);
}

const char * FileClient::GetErrorMessage() const {
    return errorMessage;
}

void FileClient::Close() {
    if (!isConnected)
        throw new ClientException(CLIENT_NOT_CONNECTED);
    if (close(sockfd) < 0) 
        throw new ClientException(FAILED_TO_CLOSE_CLIENT_SOCKET);

    isConnected = false;
}