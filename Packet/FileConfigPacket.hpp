#pragma once

#include "Packet.hpp"

namespace packet {

    class FileConfigPacket: public Packet {

        public:

        int offset;
        int numberOfBytesToRead;
        
        FileConfigPacket(int fd): Packet(fd){}

        FileConfigPacket(int fd, int offset, int numberOfBytesToRead): Packet(fd) {
            if (numberOfBytesToRead > MAX_BUFFER_SIZE) {
                numberOfBytesToRead = MAX_BUFFER_SIZE;
            }
            packetType = FILE_CONFIG_PACKET;
            this->offset = offset;
            this->numberOfBytesToRead = numberOfBytesToRead;
        }

        int getReadPacketSize() const override {
            return sizeof(offset) + sizeof(numberOfBytesToRead); 
        }

        void deserializePacket(unsigned char *buffer) override {
            buffer = deserialize_int_big_endian(buffer, &offset);
            buffer = deserialize_int_big_endian(buffer, &numberOfBytesToRead); 
        }

        unsigned char * serializePacket(unsigned char *buffer) override {
            buffer = serialize_int_big_endian(buffer, offset);
            buffer = serialize_int_big_endian(buffer, numberOfBytesToRead);
            return buffer; 
        }

    };

};

