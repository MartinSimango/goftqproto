#pragma once

#include <unistd.h>
#include <PacketConstants.h>
#include <Serializer.h>
#include <PacketException.hpp>

// TODO make all virtual functions protected methods and then make them private derived packet classes 
namespace packet {

    class Packet {
        
        private:
        int fd;

        protected: 
        int packetType;    

        public:

        Packet(int fd): fd(fd) { packetType = PACKET; } 
        virtual ~Packet() {}
        
        int GetPacketType() const { return packetType; }

        int WritePacket() {
            
            int packetByteSize = getWritePacketSize();

            unsigned char buffer[packetByteSize]; 
            unsigned char *ptr; 

            ptr = serializePacket(buffer);

            int bytes_written = write(fd, buffer, ptr - buffer);   

            if (bytes_written < 0) 
                throw new PacketException(FAILED_TO_WRITE_PACKET, packetType);
            
            return bytes_written;
        }
        
        int ReadIntoPacket(){
            int packetByteSize = getReadPacketSize();
            unsigned char buffer[packetByteSize]; 
            int bytesRead = read(fd, buffer, packetByteSize);
            
            if (bytesRead < 0) 
                throw new PacketException(FAILED_TO_READ_FROM_PACKET, packetType);

            deserializePacket(buffer);

            return bytesRead;
        }

        virtual int getReadPacketSize() const = 0;
        virtual int getWritePacketSize() const { return getReadPacketSize(); }
        virtual void deserializePacket(unsigned char *buffer) = 0;
        virtual unsigned char * serializePacket(unsigned char *buffer) = 0;
    
    };
};


    




