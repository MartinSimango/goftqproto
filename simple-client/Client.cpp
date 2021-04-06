#include "Client.hpp"

using namespace ftc;


bool FileClient::Connect(struct ServerPort serverPort){
    if (isConnected){
        errorMessage = CLIENT_ALREADY_CONNECTED;
        return false;
    }
    isConnected = connectToServer(serverPort) && requestToServer() && openFile();
    return isConnected;
}

int FileClient::Process(int offset, int numberOfBytesRead){
    if (!isConnected)
        return false;
        
    FileConfigPacket packet(sockfd, offset, numberOfBytesRead);

    return mode == READ ? readFromServer(&packet): writeToServer(&packet);
}

const char * FileClient::GetErrorMessage() const {
    return errorMessage;
}

bool FileClient::Close(){
    if (isConnected) {
        if (close(sockfd) < 0) {
            errorMessage = FAILED_TO_CLOSE_SOCKET;
            return false;
        }
        isConnected = false;
        return true;
    }
    errorMessage = CLIENT_NOT_CONNECTED;
    return false;
}