#pragma once
#include <Response.hpp>


namespace response {


    class WriteResponse : public Response
    {

    private:
        int numberOfBytesWritten;

    public:

        WriteResponse(int fd, int numberOfBytesWritten, ResponseStatus::Type status = ResponseStatus::OK): Response(fd), numberOfBytesWritten(numberOfBytesWritten) {
            this->responseType = ResponseType::WRITE;
            this->status = status;
        }

        WriteResponse(int fd): Response(fd) {
            responseType = ResponseType::WRITE;
        }


        ~WriteResponse(){}

        int getResponseBodySize() const override;

        void deserializeResponseBody(unsigned char *buffer) override;

        unsigned char * serializeResponseBody(unsigned char *buffer) override;

        std::string GetBody() const override;


    };

}
