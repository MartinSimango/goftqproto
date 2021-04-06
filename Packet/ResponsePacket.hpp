#pragma once

#include "Packet.hpp"

namespace packet {

//statuses 
#define OK  0
#define FILE_NOT_FOUND 1
#define NO_WRITE_PERMISIONS 2
#define NO_READ_PERMISSIONS 3

class ResponsePacket : public Packet {
    
    public:
    unsigned char status;

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

}