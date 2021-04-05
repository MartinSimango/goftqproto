#include "Client.hpp"

using namespace ftc;



bool FileClient::Connect(struct ServerPort *serverPort){
    if (isConnected){
        errorMessage = CLIENT_ALREADY_CONNECTED;
        return false;
    }
    isConnected = connectToServer() && requestToServer() && openFile();
    return isConnected;
}

bool FileClient::Process(struct FileReadPacket * packet){
    if(isConnected){

        if (requestPacket.mode == READ) {
            return readFromServer(packet);
        }
        else {
            return writeToServer(packet);
        }
    }
    // Not connected 
    return false;

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
        if (frw){
            delete frw;
        }
        return true;
    }
    errorMessage = CLIENT_NOT_CONNECTED;
    return false;
}