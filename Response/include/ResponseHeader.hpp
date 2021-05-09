 #pragma once
#include <Serializer.h>
#include <ResponseConstants.hpp>

namespace response {

    class ResponseHeader
    {
    private:
        int requestBodySize; 
        ResponseType::Type responseType;
        ResponseStatus::Type status;

    public:
    
        ResponseHeader(int requestBodySize, ResponseType::Type responseType, ResponseStatus::Type status): requestBodySize(requestBodySize), 
                    responseType(responseType), status(status) {}

        ResponseHeader() {}

        ~ResponseHeader();

        int getResponseHeaderSize(){
            return sizeof(requestBodySize) + sizeof(responseType) + sizeof(status);
        }

        unsigned char * serializeResponseHeader(unsigned char *buffer) {
            buffer = serialize_int_big_endian(buffer, requestBodySize);
            buffer = serialize_int_big_endian(buffer, responseType);
            buffer = serialize_int_big_endian(buffer, status);
            return buffer;
        }

        void deserializeResponseHeader(unsigned char *buffer) {
            buffer = deserialize_int_big_endian(buffer, &requestBodySize);
            buffer = deserialize_int_big_endian(buffer, (int*)&responseType); 
            buffer = deserialize_int_big_endian(buffer, (int*)&status); 
        }

        int getResponseBodySize() const {
            return requestBodySize;
        }
        
        ResponseStatus::Type getStatus() const {
            return status;
        }


    };

}
