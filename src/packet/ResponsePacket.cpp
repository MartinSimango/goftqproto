#include <ResponsePacket.hpp>

using namespace packet;

ResponsePacket::ResponsePacket(int fd): Packet(fd) {
    packetType = RESPONSE_PACKET;
}

int ResponsePacket::getReadPacketSize() const {
    return sizeof(status);
}

void ResponsePacket::deserializePacket(unsigned char *buffer) {
    buffer = deserialize_char(buffer, (char *) &status); 
}

unsigned char * ResponsePacket::serializePacket(unsigned char *buffer) {
    buffer = serialize_char(buffer, status);
    return buffer; 
}