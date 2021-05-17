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

    public:
        std::vector<request::File> * files;
        int numFiles;

        CreateResponse(int fd, std::vector<request::File> * files, ResponseStatus::Type status = ResponseStatus::OK): Response(fd), files(files) {
            this->responseType = ResponseType::CREATE;
            this->numFiles = files->size();
            this->status = status;
        }

        CreateResponse(int fd): Response(fd) {
            this->responseType = ResponseType::CREATE;
            this->files = NULL;
        }


        ~CreateResponse(){
            delete this->files;
        }

        int getResponseBodySize() const override;

        void deserializeResponseBody(unsigned char *buffer) override;

        unsigned char * serializeResponseBody(unsigned char *buffer) override;

        std::string GetBody() const override;

    };

}
