#pragma once

#include "Packet.hpp"

using namespace packet;

class ResponsePacket : Packet {
    
    private:
    unsigned char status;
    
    public:
    ResponsePacket(int fd): Packet(fd) {
        packetType = RESPONSE_PACKET;
    }

    int getReadPacketSize() const override {
        return sizeof(status);

    }

    void deserializePacket(unsigned char *buffer) override {
        buffer = deserialize_char(buffer, (char *) &status); 
    };
    
    unsigned char * serializePacket(unsigned char *buffer) override {
        buffer = serialize_char(buffer, status);
        return buffer; 
        
    };

};