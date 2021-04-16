#include <FileConfigPacket.hpp>

using namespace packet;

FileConfigPacket::FileConfigPacket(int fd): Packet(fd){
        packetType = FILE_CONFIG_PACKET;
}

FileConfigPacket::FileConfigPacket(int fd, int offset, int numberOfBytesToRead): Packet(fd) {
    if (numberOfBytesToRead > MAX_BUFFER_SIZE) {
        numberOfBytesToRead = MAX_BUFFER_SIZE;
    }
    packetType = FILE_CONFIG_PACKET;
    this->offset = offset;
    this->numberOfBytesToRead = numberOfBytesToRead;
}

int FileConfigPacket::getReadPacketSize() const {
    return sizeof(offset) + sizeof(numberOfBytesToRead); 
}

void FileConfigPacket::deserializePacket(unsigned char *buffer){
    buffer = deserialize_int_big_endian(buffer, &offset);
    buffer = deserialize_int_big_endian(buffer, &numberOfBytesToRead); 
}

unsigned char * FileConfigPacket::serializePacket(unsigned char *buffer){
    buffer = serialize_int_big_endian(buffer, offset);
    buffer = serialize_int_big_endian(buffer, numberOfBytesToRead);
    return buffer; 
}



