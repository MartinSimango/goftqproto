#include <FilePacket.hpp>

using namespace packet;

FilePacket::FilePacket(int fd): Packet(fd){
    packetType = FILE_PACKET;
}

FilePacket::FilePacket(int fd, char * data, int bytesRead, int offset): Packet(fd) {
    packetType = FILE_PACKET;
    //TODO check that sizeof(this->data) is greater than or equal to sizeof(data) 
    if (data){
        strlcpy(this->data, data, sizeof(this->data));
    }
    this->numberOfBytesRead = bytesRead;
}


int FilePacket::getReadPacketSize() const {
    return sizeof(numberOfBytesRead) + sizeof(offset) + sizeof(data);
}

int FilePacket::getWritePacketSize() const {
    printf("Printing from File Packet!\n");
    return sizeof(numberOfBytesRead) + sizeof(offset) + strlen(data) + 1;  // +1 to accomodate for '\0' character
}

void FilePacket::deserializePacket(unsigned char *buffer) {
    buffer = deserialize_int_big_endian(buffer, &numberOfBytesRead);
    buffer = deserialize_int_big_endian(buffer, &offset);
    buffer = deserialize_char_array(buffer, data); 

}

unsigned char * FilePacket::serializePacket(unsigned char *buffer) {
    buffer = serialize_int_big_endian(buffer, numberOfBytesRead);
    buffer = serialize_int_big_endian(buffer, offset);
    buffer = serialize_char_array(buffer, data);
    return buffer; 
}


