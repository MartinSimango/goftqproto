#pragma once

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <Response.hpp>
#include <CreateRequest.hpp>


namespace response {


    class CreateResponse : public Response
    {

    private:
        std::vector<request::File> * files;
        int numFiles;

    public:

        CreateResponse(int fd, std::vector<request::File> * files): Response(fd), files(files) {
            responseType = ResponseType::CREATE;
            numFiles = files->size();
        }

        CreateResponse(int fd): Response(fd) {
            responseType = ResponseType::CREATE;
        }


        ~CreateResponse(){}

        int getResponseBodySize() const override;

        void deserializeResponse(unsigned char *buffer) override;

        unsigned char * serializeResponse(unsigned char *buffer) override;

    };

}
