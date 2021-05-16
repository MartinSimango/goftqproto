#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <Request.hpp>

#define MAX_FILEPATH_LENGTH 100


namespace request {

    struct File
    {
        char filename[MAX_FILEPATH_LENGTH];
        int fileSize;

        int getSize() {
            return strlen(filename) + 1 + sizeof(fileSize);
        }

        void setFileName(char * filename){
            strncpy(this->filename, filename, sizeof(this->filename));
        }

        void deserializeRequestFile(unsigned char *buffer){
            buffer = deserialize_char_array(buffer, filename);
            buffer = deserialize_int_big_endian(buffer, &fileSize); 
                std::cout << "NUMBER: asf " << filename << " " << fileSize << std::endl;

        }

        unsigned char * serializeRequestFile(unsigned char *buffer) {
            buffer = serialize_char_array(buffer, filename);
            buffer = serialize_int_big_endian(buffer, fileSize);
                            std::cout << "NUMBER: asf " << filename << " " << fileSize << std::endl;


            return buffer;
        }

    };

    class CreateRequest : public Request
    {


    public:

        std::vector<request::File> * files;
        int numFiles;

        CreateRequest(int fd, std::vector<request::File> * files): request::Request(fd), files(files) {
            this->requestType = RequestType::CREATE;
            this->numFiles = files->size();
        }

        CreateRequest(int fd, RequestHeader * requestHeader): request::Request(fd){
            this->requestType = RequestType::CREATE;

            delete this->header;
            this->header = requestHeader;
        }


        ~CreateRequest(){}

        int getRequestBodySize() const override;

        void deserializeRequestBody(unsigned char *buffer) override;

        unsigned char * serializeRequestBody(unsigned char *buffer) override;

        std::string GetBody() const override;

    };

}
