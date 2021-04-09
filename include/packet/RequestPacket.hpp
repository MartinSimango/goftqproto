#pragma once

#include <Packet.hpp>

namespace packet {

    class RequestPacket: public Packet {

        // TODO make instance variablles private and make getters and setters
        public:
        bool mode;
        char filepath[MAX_FILEPATH_LENGTH];

        RequestPacket(int fd);

        RequestPacket(int fd, bool mode, char * filepath);

        int getReadPacketSize() const override;

        int getWritePacketSize() const override;

        void deserializePacket(unsigned char *buffer) override;

        unsigned char * serializePacket(unsigned char *buffer) override;

    };


};
