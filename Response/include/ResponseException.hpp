#pragma once

#include <Exception.hpp>
#include <ResponseConstants.hpp>
#include <errno.h>

static const char * FAILED_TO_WRITE_RESPONSE = "Failed to write response.";
static const char * FAILED_TO_READ_RESPONSE = "Failed to read response.";

static const char * FAILED_TO_WRITE_RESPONSE_HEADER = "Failed to write response header";
static const char * FAILED_TO_READ_RESPONSE_HEADER = "Failed to read response header.";



namespace response {

    class ResponseException : public error::Exception {
        
        private:
            const char* error;
            ResponseType::Type responseType;
        
        public:
            ResponseException(const char *error, ResponseType::Type responseType) : error::Exception(), error(error), responseType(responseType) {}
            
            const char * what() const throw() override {
                return error;   
            }

            ResponseType::Type getRequestType() const {
                return responseType;
            }
            // TODO maybe move request type name to individual request classes
            const char * getRequestTypeName() const {
                switch (responseType)
                {
                case ResponseType::HEADER:
                    return "Request Header";
                case ResponseType::CREATE:
                    return "CREATE Response";
                case ResponseType::GET:
                    return "GET Response";
                case ResponseType::READ:
                    return "READ Response";
                case ResponseType::WRITE:
                    return "WRITE Response";
                default:
                    return "Unknown Response Type";
                    break;
                }
            }

            char * getErrorMessage(char * error) override {
                sprintf(error, 
                    "[Error] %s\n[ResponseException] Error: %s\nPacketType: [%i] - %s.",
                    strerror(errno),
                    this->error, this->responseType, 
                    getRequestTypeName());

                return error;
            }

    };

}