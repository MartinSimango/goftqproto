#include <ResponsePacket.hpp>

using namespace packet;

ResponsePacket::ResponsePacket(int fd): Packet(fd) {
    packetType = RESPONSE_PACKET;
    fileSize = -1; //undefined size 
}

int ResponsePacket::getReadPacketSize() const {
    return sizeof(status) + sizeof(fileSize);
}

void ResponsePacket::deserializePacket(unsigned char *buffer) {
    buffer = deserialize_char(buffer, (char *) &status); 
    buffer = deserialize_int_big_endian(buffer, &fileSize);
}

unsigned char * ResponsePacket::serializePacket(unsigned char *buffer) {
    buffer = serialize_char(buffer, status);
    buffer = serialize_int_big_endian(buffer, fileSize);
    return buffer; 
}