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

        void deserializeRequestFile(unsigned char *buffer){
            buffer = deserialize_char_array(buffer, filename);
            buffer = deserialize_int_big_endian(buffer, &fileSize); 
        }

        unsigned char * serializeRequestFile(unsigned char *buffer) {
            buffer = serialize_char_array(buffer, filename);
            buffer = serialize_int_big_endian(buffer, fileSize);
        }

    };

    class CreateRequest : public Request
    {

    private:
        std::vector<request::File> * files;
        int numFiles;

    public:

        CreateRequest(int fd, std::vector<request::File> * files): request::Request(fd), files(files) {
            requestType = RequestType::CREATE;
            numFiles = files->size();
        }

        CreateRequest(int fd): request::Request(fd){
            requestType = RequestType::CREATE;
        }


        ~CreateRequest(){}

        int getRequestSize() const override;

        void deserializeRequest(unsigned char *buffer) override;

        unsigned char * serializeRequest(unsigned char *buffer) override;

    };

}
