#pragma once
#include <Serializer.h>
#include <RequestConstants.hpp>

namespace request {
    class RequestHeader
    {
    private:
        int requestBodySize; 
        int fd;
        
    public:
        RequestType::Type requestType;

        RequestHeader(int requestBodySize, RequestType::Type requestType): requestBodySize(requestBodySize), requestType(requestType){}

        RequestHeader(int fd): fd(fd) {
            this->requestType = RequestType::HEADER;
        }

        ~RequestHeader(){};

        int getRequestHeaderSize();

        unsigned char * serializeRequestHeader(unsigned char *buffer);

        void deserializeRequestHeader(unsigned char *buffer);

        int getRequestBodySize() const;

        int Read();

    };

}
