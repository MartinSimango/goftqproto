#pragma once

#include <Packet.hpp>

namespace packet {

    class ResponsePacket : public Packet {
        
        public:
        
        unsigned char status;

        ResponsePacket(int fd);

        int getReadPacketSize() const override;

        void deserializePacket(unsigned char *buffer) override;

        unsigned char * serializePacket(unsigned char *buffer) override;

    };

}