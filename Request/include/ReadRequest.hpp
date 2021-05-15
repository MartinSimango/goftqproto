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

        ReadRequest(int fd, RequestHeader * requestHeader): request::Request(fd) {
            requestType = RequestType::READ;

            delete this->header;
            this->header = requestHeader;
        }

        ~ReadRequest(){}

        int getRequestBodySize() const override;

        void deserializeRequestBody(unsigned char *buffer) override;

        unsigned char * serializeRequestBody(unsigned char *buffer) override;
        
        std::string GetBody() const override;


    };

}