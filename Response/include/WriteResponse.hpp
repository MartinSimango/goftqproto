#pragma once
#include <Response.hpp>


namespace response {


    class WriteResponse : public Response
    {

    private:
        int numberOfBytesWritten;

    public:

        WriteResponse(int fd, int numberOfBytesWritten): Response(fd), numberOfBytesWritten(numberOfBytesWritten) {
            responseType = ResponseType::WRITE;
        }

        WriteResponse(int fd): Response(fd) {
            responseType = ResponseType::WRITE;
        }


        ~WriteResponse(){}

        int getResponseBodySize() const override;

        void deserializeResponse(unsigned char *buffer) override;

        unsigned char * serializeResponse(unsigned char *buffer) override;

    };

}
