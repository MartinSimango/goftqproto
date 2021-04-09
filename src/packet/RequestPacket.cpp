#include <RequestPacket.hpp>

using namespace packet;


RequestPacket::RequestPacket(int fd): Packet(fd){
    packetType = REQUEST_PACKET;
}

RequestPacket::RequestPacket(int fd, bool mode, char * filepath): Packet(fd) {
    packetType = REQUEST_PACKET;
    this->mode = mode;
    if (filepath) {
        strlcpy(this->filepath, filepath, sizeof(this->filepath));
    }
}

int RequestPacket::getReadPacketSize() const {
    return sizeof(mode) + sizeof(filepath);
}

int RequestPacket::getWritePacketSize() const {

    return sizeof(mode) + strlen(filepath) + 1;  // +1 to accomodate for '\0' character
}

void RequestPacket::deserializePacket(unsigned char *buffer) {
    buffer = deserialize_char(buffer, (char *) &mode);
    buffer = deserialize_char_array(buffer, filepath); 
}

unsigned char * RequestPacket::serializePacket(unsigned char *buffer) {
    buffer = serialize_char(buffer, mode);
    buffer = serialize_char_array(buffer, filepath);
    return buffer; 
}

 