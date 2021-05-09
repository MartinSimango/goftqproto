#pragma once

#include <unistd.h>
#include <Serializer.h>
#include <RequestConstants.hpp>
#include <RequestException.hpp>
#include <errno.h>
#include <RequestHeader.hpp>

// TODO make all virtual functions protected methods and then make them private derived request classes 
namespace request {

    class Request {
        
        private:
        int fd;

        protected: 
        RequestType::Type requestType;  
        RequestHeader * header;

        public:

        Request(int fd): fd(fd) {  requestType = RequestType::UNKNOWN; } 
        virtual ~Request() { 
            delete header;
            header = NULL;
        }
        
        RequestType::Type GetRequestType() const { return requestType; }

        int WriteRequest();
        int ReadRequest();
         
        virtual int getRequestSize() const = 0;
        virtual void deserializeRequest(unsigned char *buffer) = 0;
        virtual unsigned char * serializeRequest(unsigned char *buffer) = 0;
    
    
    };
};


    




