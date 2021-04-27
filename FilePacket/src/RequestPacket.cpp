#include <RequestPacket.hpp>

using namespace packet;


RequestPacket::RequestPacket(int fd): Packet(fd){
    packetType = REQUEST_PACKET;
    this->fileSize = 0;
}

RequestPacket::RequestPacket(int fd, bool mode, char * filepath,int fileSize): Packet(fd) {
    packetType = REQUEST_PACKET;
    this->mode = mode;
    if (filepath) {
        strlcpy(this->filepath, filepath, sizeof(this->filepath));
    }
    this->fileSize = fileSize;
}

int RequestPacket::getReadPacketSize() const {
    return sizeof(mode) + sizeof(filepath) + sizeof(fileSize);
}

int RequestPacket::getWritePacketSize() const {

    return sizeof(mode) + strlen(filepath) + 1 + sizeof(fileSize);  // +1 to accomodate for '\0' character
}

void RequestPacket::deserializePacket(unsigned char *buffer) {
    buffer = deserialize_char(buffer, (char *) &mode);
    buffer = deserialize_char(buffer, (char *) &createFile);
    buffer = deserialize_int_big_endian(buffer, &fileSize);   
    buffer = deserialize_char_array(buffer, filepath); 
}

unsigned char * RequestPacket::serializePacket(unsigned char *buffer) {
    buffer = serialize_char(buffer, mode);
    buffer = serialize_char(buffer, createFile);
    buffer = serialize_int_big_endian(buffer, fileSize);
    buffer = serialize_char_array(buffer, filepath);

    return buffer; 
}

 