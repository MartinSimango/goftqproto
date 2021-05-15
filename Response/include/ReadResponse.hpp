#pragma once
#include <Response.hpp>
#include <RequestConstants.hpp>

namespace response {


    class ReadResponse : public Response
    {

    public:

        int numberOfBytesRead;
        char data[MAX_BUFFER_SIZE];

        ReadResponse(int fd, int numberOfBytesRead, char * data, ResponseStatus::Type status = ResponseStatus::OK): Response(fd), numberOfBytesRead(numberOfBytesRead) {
            responseType = ResponseType::READ;
            this->status = status;
            strlcpy(this->data, data, sizeof(this->data));
        }

        ReadResponse(int fd): Response(fd) {
            responseType = ResponseType::READ;
        }


        ~ReadResponse(){}

        int getResponseBodySize() const override;

        void deserializeResponseBody(unsigned char *buffer) override;

        unsigned char * serializeResponseBody(unsigned char *buffer) override;

        std::string GetBody() const override;

    };

}
