#pragma once

#pragma once
#include <iostream>
#include <exception>
#include <PacketConstants.h>

static const char * FAILED_TO_WRITE_PACKET = "Failed to write packet.";
static const char * FAILED_TO_READ_FROM_PACKET = "Failed to read from packet.";



class PacketException : public std::exception {
    
    private:
	    const char* error;
        int packetType;
    
    public:
        PacketException(const char *error, int packetType) : std::exception(), error(error){}
    	
        const char * what() const override {
            return error;   
        }

        int packetType() const {
            return packetType;
        }
        // TODO maybe move packet type name to individual packet classes
        const char * packetTypeName() const {
            switch (packetType)
            {
            case PACKET:
                return "Packet";
            case FILE_CONFIG_PACKET:
                return "File Config Packet";
            case FILE_PACKET:
                return "File Packet";
            case REQUEST_PACKET:
                return "Request Packet";
            case RESPONSE_PACKET:
                return "Response Packet";
            default:
                return "Unknown Packet Type";
                break;
            }
        }

};

