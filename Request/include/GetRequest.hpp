#pragma once
#include <Request.hpp>
#include <FileReadWriterConstants.h>

namespace request {

    class GetRequest: public Request
    {
    private:
        char filepath[MAX_FILEPATH_LENGTH];
    public:
        GetRequest(int fd): request::Request(fd) {
            requestType = RequestType::GET;
        }
        GetRequest(int fd, char* filepath): request::Request(fd) {
            requestType = RequestType::GET;
            strlcpy(this->filepath, filepath, sizeof(this->filepath));
        }

        ~GetRequest();
        
        int getRequestSize() const override;

        void deserializeRequest(unsigned char *buffer) override;

        unsigned char * serializeRequest(unsigned char *buffer) override;

    };

}

