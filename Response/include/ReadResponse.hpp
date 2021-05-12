#pragma once
#include <Response.hpp>


namespace response {


    class ReadResponse : public Response
    {

    private:
        int numberOfBytesRead;

    public:

        ReadResponse(int fd, int numberOfBytesRead): Response(fd), numberOfBytesRead(numberOfBytesRead) {
            responseType = ResponseType::READ;
        }

        ReadResponse(int fd): Response(fd) {
            responseType = ResponseType::READ;
        }


        ~ReadResponse(){}

        int getResponseBodySize() const override;

        void deserializeResponse(unsigned char *buffer) override;

        unsigned char * serializeResponse(unsigned char *buffer) override;

    };

}
