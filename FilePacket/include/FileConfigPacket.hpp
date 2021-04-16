#pragma once

#include <Packet.hpp>

namespace packet {

    class FileConfigPacket: public Packet {

        public:
        int offset;
        int numberOfBytesToRead;
        
        FileConfigPacket(int fd);

        FileConfigPacket(int fd, int offset, int numberOfBytesToRead);

        ~FileConfigPacket() override {}

        int getReadPacketSize() const override;

        void deserializePacket(unsigned char *buffer) override;

        unsigned char * serializePacket(unsigned char *buffer) override;

    };

};

