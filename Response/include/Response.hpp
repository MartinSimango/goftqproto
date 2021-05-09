#pragma once

#include <unistd.h>
#include <Serializer.h>
#include <ResponseConstants.hpp>
#include <ResponseException.hpp>
#include <errno.h>
#include <ResponseHeader.hpp>

// TODO make all virtual functions protected methods and then make them private derived request classes 
namespace response {

    class Response {
        
        private:
        int fd;

        protected: 
        ResponseType::Type responseType;  
        ResponseHeader * header;

        public:

        Response(int fd): fd(fd) { responseType = ResponseType::UNKNOWN; } 
        virtual ~Response() { 
            delete header;
            header = NULL;
        }
        
        ResponseType::Type GetResponseType() const { return responseType; }

        int WriteResponse();
        int ReadResponse();
         
        virtual int getResponseBodySize() const = 0;
        virtual void deserializeResponse(unsigned char *buffer) = 0;
        virtual unsigned char * serializeResponse(unsigned char *buffer) = 0;
    
    
    };
};


