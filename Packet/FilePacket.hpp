#pragma once
#include "Packet.hpp"

namespace packet {
    
//FilePacket containts the conent of the file
    class FilePacket : Packet {
        
        private:
        int numberOfBytesRead;
        char data[MAX_BUFFER_SIZE]; 

        FilePacket(int fd, char * data, int bytes_read): Packet(fd) {
            packetType = FILE_PACKET;
            
            strcpy(this->data, data);
            this->numberOfBytesRead = bytes_read;
        }

        int getReadPacketSize() const override {
            return sizeof(numberOfBytesRead) + sizeof(data);
        }

        int getWritePacketSize() const override {
            return sizeof(numberOfBytesRead) + strlen(data) + 1;  // +1 to accomodate for '\0' character
        }

        void deserializePacket(unsigned char *buffer) override {
            buffer = deserialize_int_big_endian(buffer, &numberOfBytesRead);
            buffer = deserialize_char_array(buffer, data); 

        }

        unsigned char * serializePacket(unsigned char *buffer) override {
            buffer = serialize_int_big_endian(buffer, numberOfBytesRead);
            buffer = serialize_char_array(buffer, data);
            return buffer; 
        }

    };

};
