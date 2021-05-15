#pragma once

#include <Exception.hpp>
#include <RequestConstants.hpp>
#include <errno.h>

static const char * FAILED_TO_WRITE_REQUEST = "Failed to write request.";
static const char * FAILED_TO_READ_REQUEST = "Failed to read from request.";
static const char * FAILED_TO_WRITE_REQUEST_HEADER = "Failed to write request header.";
static const char * FAILED_TO_READ_REQUEST_HEADER = "Failed to read request header.";


namespace request {

    class RequestException : public error::Exception {
        
        private:
            const char* error;
            RequestType::Type requestType;
        
        public:
            RequestException(const char *error, RequestType::Type requestType) : error::Exception(), error(error), requestType(requestType) {}
            
            const char * what() const throw() override {
                return error;   
            }

            RequestType::Type getRequestType() const {
                return requestType;
            }
            // TODO maybe move request type name to individual request classes
            const char * getRequestTypeName() const {
                switch (requestType)
                {
                case RequestType::HEADER:
                    return "Request Header";
                case RequestType::CREATE:
                    return "CREATE Request";
                case RequestType::GET:
                    return "GET Request";
                case RequestType::READ:
                    return "READ Request";
                case RequestType::WRITE:
                    return "WRITE Request";
                default:
                    return "Unknown Request Type";
                    break;
                }
            }

            char * getErrorMessage(char * error) override {
                sprintf(error, 
                    "[Error] %s\n[RequestException] Error: %s\nPacketType: [%i] - %s.",
                    strerror(errno),
                    this->error, this->requestType, 
                    getRequestTypeName());

                return error;
            }

    };

}