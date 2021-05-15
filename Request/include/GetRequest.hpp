#pragma once
#include <Request.hpp>
#include <FileReadWriterConstants.h>

namespace request {

    class GetRequest: public Request
    {
    private:
        char filepath[MAX_FILEPATH_LENGTH];
    public:
        GetRequest(int fd, RequestHeader * requestHeader): Request(fd) {
            requestType = RequestType::GET;

            delete this->header;
            this->header = requestHeader;
        }
        GetRequest(int fd, char* filepath): Request(fd) {
            requestType = RequestType::GET;
            strlcpy(this->filepath, filepath, sizeof(this->filepath));
        }

        ~GetRequest(){}
        
        int getRequestBodySize() const override;

        void deserializeRequestBody(unsigned char *buffer) override;

        unsigned char * serializeRequestBody(unsigned char *buffer) override;

        std::string GetBody() const override;


    };

}

