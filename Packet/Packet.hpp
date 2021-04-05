#pragma once

#include <unistd.h>
#include "PacketConstants.h"

#include "../serialize.h"

namespace packet {

    class Packet {
        
        private:
        int fd;

        protected: 
        int packetType;    

        public:
        Packet(int fd): fd(fd) { packetType = PACKET; } 
        //virtual ~Packet() {}
        int getPacketType() const { return packetType; }
        int WritePacket() {
            
            int packetByteSize = getWritePacketSize();

            unsigned char buffer[packetByteSize]; 
            unsigned char *ptr; 

            ptr = serializePacket(buffer);

            return write(fd, buffer, ptr - buffer);   
        }
        
        int ReadIntoPacket(){
            
            int packetByteSize = getReadPacketSize();
            unsigned char buffer[packetByteSize]; 
            unsigned char *ptr; //ptr will point to the end of the array of data bytes to be written 

            int bytesRead = read(fd, buffer, packetByteSize);
            if (bytesRead >= 0) {
                deserializePacket(buffer);
            }
                    //TODO handle errors

            return bytesRead;
            
        }
        virtual int getReadPacketSize() const = 0;
        virtual int getWritePacketSize() const { return getReadPacketSize(); }
        virtual void deserializePacket(unsigned char *buffer) = 0;
        virtual unsigned char * serializePacket(unsigned char *buffer) = 0;
    
    };
};


    

// struct FileReadPacket {
//     int offset; // where to start reading
//     int numberOfBytesToRead; //max number of bytes to read
// };




