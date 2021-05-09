#pragma once
#include <FileReadWriterConstants.h>
#include <Request.hpp>

namespace request {

    class ReadRequest : public Request
    {
      
    public:
        int offset, numberOfBytesToRead;
        char filename[MAX_FILEPATH_LENGTH];

        ReadRequest(int fd, char *filename ,int offset, int numberOfBytesToRead): request::Request(fd) {
            if (numberOfBytesToRead > MAX_BUFFER_SIZE) {
                 numberOfBytesToRead = MAX_BUFFER_SIZE;
            }

            strlcpy(this->filename, filename, sizeof(this->filename));
            requestType = RequestType::READ;
            this->offset = offset;
            this->numberOfBytesToRead = numberOfBytesToRead;
        }

        ReadRequest(int fd): request::Request(fd) {
            requestType = RequestType::READ;
        }

        ~ReadRequest();

        int getRequestSize() const override;

        void deserializeRequest(unsigned char *buffer) override;

        unsigned char * serializeRequest(unsigned char *buffer) override;

    };

}