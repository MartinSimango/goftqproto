#pragma once

#include <FileReadWriterConstants.h>
#include <Request.hpp>

namespace request {

    class WriteRequest : public request::Request
    {
      
    public:
        int offset, numberOfBytesToWrite;
        char data[MAX_BUFFER_SIZE], filepath[MAX_FILEPATH_LENGTH];

        WriteRequest(int fd, char* data, int offset, int numberOfBytesToWrite, char* filepath): request::Request(fd) {
            if (numberOfBytesToWrite > MAX_BUFFER_SIZE) {
                 numberOfBytesToWrite = MAX_BUFFER_SIZE;
            }

            strlcpy(this->data, data, sizeof(this->data));

            strlcpy(this->filepath, filepath, sizeof(this->filepath));

            requestType = RequestType::READ;
            this->offset = offset;
            this->numberOfBytesToWrite = numberOfBytesToWrite;
        }

        WriteRequest(int fd): request::Request(fd) {
            requestType = RequestType::WRITE;
        }

        ~WriteRequest();

        int getRequestSize() const override;

        void deserializeRequest(unsigned char *buffer) override;

        unsigned char * serializeRequest(unsigned char *buffer) override;

    };

}