#pragma once
#include <Response.hpp>
#include <CreateRequest.hpp>
#include <FileReadWriterConstants.h>

namespace response {

    class GetResponse: public Response
    {
    private:
        std::vector<request::File> * files;
        int numFiles;
    public:
        GetResponse(int fd): Response(fd) {
            responseType = ResponseType::GET;
        }

        GetResponse(int fd, std::vector<request::File> * files): Response(fd), files(files) {
            responseType = ResponseType::GET;
            this->numFiles = files->size();
        }

        ~GetResponse();
        
        int getResponseBodySize() const override;

        void deserializeResponse(unsigned char *buffer) override;

        unsigned char * serializeResponse(unsigned char *buffer) override;

    };

}

