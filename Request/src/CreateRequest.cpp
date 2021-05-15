#include <CreateRequest.hpp>

using namespace request;

int CreateRequest::getRequestBodySize() const {
    int fileSize = 0;
    for (int i = 0; i < numFiles; i++) {
        fileSize += files->at(i).getSize();
    }
    return fileSize + sizeof(numFiles);
}

void CreateRequest::deserializeRequestBody(unsigned char *buffer){
    
    buffer = deserialize_int_big_endian(buffer, &numFiles);
    delete this->files;
    files = new std::vector<request::File>(numFiles);
    for (int i = 0; i < numFiles; i++) {
        files->at(i).deserializeRequestFile(buffer);
    }
}

unsigned char * CreateRequest::serializeRequestBody(unsigned char *buffer){
        
    buffer = serialize_int_big_endian(buffer, numFiles);

    for (int i = 0; i < numFiles; i++) {
        buffer = files->at(i).serializeRequestFile(buffer);
    }
    return buffer; 
}

std::string CreateRequest::GetBody() const {
    return "{ }";
}