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
        ResponseHeader * header;

        public:
        ResponseType::Type responseType;  
        ResponseStatus::Type status;


        Response(int fd): fd(fd) { 
            responseType = ResponseType::UNKNOWN;
            status = ResponseStatus::OK;
            this->header = NULL;
        } 

        Response(int fd, ResponseStatus::Type status): fd(fd), status(status) { 
            this->header = NULL;
            this->responseType = ResponseType::UNKNOWN; 
        } 

        virtual ~Response() { 
            delete header;
            header = NULL;
        }
        
        ResponseType::Type GetResponseType() const { return responseType; }

        ResponseHeader * GetHeader() const { return header; }

        int Write();
        
        int Read();

        int WriteBody();

        int ReadBody();

        int WriteHeader();

        int ReadHeader();

        virtual int getResponseBodySize() const = 0;
        virtual void deserializeResponseBody(unsigned char *buffer) = 0;
        virtual unsigned char * serializeResponseBody(unsigned char *buffer) = 0;
        virtual std::string GetBody() const = 0;
    
    };
};


