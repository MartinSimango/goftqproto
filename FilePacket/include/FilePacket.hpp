#pragma once

#include <Packet.hpp>

namespace packet {

//FilePacket containts the conent of the file
    class FilePacket : public Packet {
        
        public:
        int numberOfBytesRead;
        int offset;
        char data[MAX_BUFFER_SIZE]; 

        FilePacket(int fd);

        FilePacket(int fd, char * data, int bytesRead, int offset);
        
        int getReadPacketSize() const override;

        int getWritePacketSize() const override;

        void deserializePacket(unsigned char *buffer) override;

        unsigned char * serializePacket(unsigned char *buffer) override;
    };

};
