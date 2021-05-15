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
        bool headerRead, headerWritten;

        protected: 
        RequestType::Type requestType;  
        RequestHeader * header;

        public:

        Request(int fd): fd(fd) { 
            this->header = NULL;
            requestType = RequestType::UNKNOWN;
        }

        Request(int fd, RequestHeader * header): fd(fd) {
            this->header = header;
            requestType = RequestType::UNKNOWN;
        }

        virtual ~Request() { 
            delete header;
            header = NULL;
        }
        
        RequestType::Type GetRequestType() const { return requestType; }

        RequestHeader* GetRequestHeader() const { return header; }

        int Write();

        int Read();

        int WriteBody();

        int ReadBody();

        int WriteHeader();

        int ReadHeader();
         
        virtual int getRequestBodySize() const = 0;

        virtual void deserializeRequestBody(unsigned char *buffer) = 0;

        virtual unsigned char * serializeRequestBody(unsigned char *buffer) = 0;

        virtual std::string GetBody() const = 0;    
    };
};


    




