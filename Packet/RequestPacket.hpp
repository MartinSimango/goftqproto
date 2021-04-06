#pragma once
#include "Packet.hpp"

namespace packet {

#define WRITE 0
#define READ 1

    class RequestPacket: public Packet {

        // TODO make instance variablles private and make getters and setters
        public:
        bool mode;
        char filepath[MAX_FILEPATH_LENGTH];

        RequestPacket(int fd): Packet(fd){}

        RequestPacket(int fd, bool mode, char * filepath): Packet(fd) {
            packetType = REQUEST_PACKET;
            this->mode = mode;
            if (filepath) {
                strlcpy(this->filepath, filepath, sizeof(this->filepath));
            }
        }

        int getReadPacketSize() const override {
            return sizeof(mode) + sizeof(filepath);
        }

        int getWritePacketSize() const override {

            return sizeof(mode) + strlen(filepath) + 1;  // +1 to accomodate for '\0' character
        }

        void deserializePacket(unsigned char *buffer) override {
            buffer = deserialize_char(buffer, (char *) &mode);
            buffer = deserialize_char_array(buffer, filepath); 
        }

        unsigned char * serializePacket(unsigned char *buffer) override {
            buffer = serialize_char(buffer, mode);
            buffer = serialize_char_array(buffer, filepath);
            return buffer; 
        }

    };


};
