#pragma once
#include <Serializer.h>
#include <RequestConstants.hpp>

namespace request {
    class RequestHeader
    {
    private:
        int requestBodySize; 
        RequestType::Type requestType;
        
    public:
    
        RequestHeader(int requestBodySize, RequestType::Type requestType): requestBodySize(requestBodySize), requestType(requestType){}

        RequestHeader() {}

        ~RequestHeader();

        int getRequestHeaderSize(){
            return sizeof(requestBodySize) + sizeof(requestType);
        }

        unsigned char * serializeRequestHeader(unsigned char *buffer) {
            buffer = serialize_int_big_endian(buffer, requestBodySize);
            buffer = serialize_int_big_endian(buffer, requestType);
            return buffer;
        }

        void deserializeRequestHeader(unsigned char *buffer) {
            buffer = deserialize_int_big_endian(buffer, &requestBodySize);
            buffer = deserialize_int_big_endian(buffer, (int*)&requestType); 

        }

        int getRequestBodySize() const {
            return requestBodySize;
        }


    };

}
