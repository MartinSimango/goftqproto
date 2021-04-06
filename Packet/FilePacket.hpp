#pragma once
#include "Packet.hpp"

namespace packet {

//FilePacket containts the conent of the file
// TODO sepate into file packet read and file packer write as when reading from server number of bytes doesnt need to be set
    class FilePacket : public Packet {
        
        public:
        int numberOfBytesRead;
        int offset;
        char data[MAX_BUFFER_SIZE]; 

        FilePacket(int fd): Packet(fd){}
        FilePacket(int fd, char * data, int bytesRead, int offset): Packet(fd) {
            packetType = FILE_PACKET;
            //TODO check that sizeof(this->data) is greater than or equal to sizeof(data) 
            if (data){
                strlcpy(this->data, data, sizeof(this->data));
            }
            this->numberOfBytesRead = bytesRead;
        }
        

        int getReadPacketSize() const override {
            return sizeof(numberOfBytesRead) + sizeof(offset) + sizeof(data);
        }

        int getWritePacketSize() const override {
            printf("Printing from File Packet!\n");
            return sizeof(numberOfBytesRead) + sizeof(offset) + strlen(data) + 1;  // +1 to accomodate for '\0' character
        }

        void deserializePacket(unsigned char *buffer) override {
            buffer = deserialize_int_big_endian(buffer, &numberOfBytesRead);
            buffer = deserialize_int_big_endian(buffer, &offset);
            buffer = deserialize_char_array(buffer, data); 

        }

        unsigned char * serializePacket(unsigned char *buffer) override {
            buffer = serialize_int_big_endian(buffer, numberOfBytesRead);
            buffer = serialize_int_big_endian(buffer, offset);
            buffer = serialize_char_array(buffer, data);
            return buffer; 
        }

    };

};
