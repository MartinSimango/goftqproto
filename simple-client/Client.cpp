#include "Client.hpp"

using namespace ftc;



bool FileClient::Connect(struct ServerPort *serverPort){
    if (isConnected){
        errorMessage = CLIENT_ALREADY_CONNECTED;
        return false;
    }
    return isConnected = connectToServer();
}


bool FileClient::WriteToServer(struct FileReadWritePacket *readPacket, char * serverFileName = nullptr){
    if (!isConnected) {
        errorMessage = CLIENT_NOT_CONNECTED;
        return false;
    }  

    if (serverFileName == nullptr){
        strcpy(serverFileName, readPacket->filename);
    }
    
    if(!requestToServer(WRITE, serverFileName)) {
        return false;
    }

    FileReadWriter *frw = new FileReadWriter(readPacket->filename, READ);
    if (frw->Open()) {
        errorMessage = FAILED_TO_OPEN_FILE;
        return false;
    }


    int bytes_read;
    char data_read[TRANSFER_DATA_SIZE]; //be prepared to read a MEGABYTE of data

    if ((bytes_read = frw->ReadFromFile(data_read, readPacket->bytesToReadWrite, readPacket->offset)) < 0) {
        errorMessage = FAILED_TO_READ_FROM_FILE;
        return false;
    }

    // TODO make a factory for making the file packet

    struct FilePacket packet;
    strcpy(packet.data, data_read);
    strcpy(packet.filename, serverFileName);
    packet.offset = readPacket->offset;
    packet.mode = WRITE;
    packet.bytes_rw = bytes_read; 

    unsigned char buffer[get_size_of_file_packet(&packet)];  //buffer will point to the start of the array of data bytes to be written and is where data is stored
    unsigned char *ptr; //ptr will point to the end of the array of data bytes to be written 

    ptr = serialize_file_packet(buffer, &packet);

    write_serialized_data(sockfd, buffer, ptr);

    // TODO add check for when server responds

    delete frw;
    return true;
}

bool FileClient::ReadFromServer(struct FileReadWritePacket * writePacket, char * serverFileName = nullptr){
    if (!isConnected) {
        errorMessage = CLIENT_NOT_CONNECTED;
        return false;
    }   

     if (serverFileName == nullptr){
        strcpy(serverFileName, writePacket->filename);
    }
    if(!requestToServer(READ, serverFileName)){
        return false;
    }
   

    FileReadWriter *frw = new FileReadWriter(writePacket->filename, WRITE);
    if (frw->Open()) {
        errorMessage = FAILED_TO_OPEN_FILE;
        return false;
    }


    int bytes_read;
    unsigned char buffer[TRANSFER_DATA_SIZE];

    if ((bytes_read = read(sockfd, buffer, TRANSFER_DATA_SIZE)) < 0){
        errorMessage = FAILED_TO_READ_FROM_SERVER_SOCKET;
        return false;
    }
    
    struct FilePacket packet;
    deserialize_file_packet(buffer, &packet);
   

    if ((bytes_read = frw->WriteToFile(packet.data, packet.bytes_rw, packet.offset)) < 0) {
        errorMessage = FAILED_TO_READ_FROM_FILE;
        return false;
    }

    return true;
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