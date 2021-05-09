#include <CreateRequest.hpp>

using namespace request;

int CreateRequest::getRequestSize() const {
    int fileSize = 0;
    for (int i = 0; i < numFiles; i++) {
        fileSize += files->at(i).getSize();
    }
    return fileSize;
}

void CreateRequest::deserializeRequest(unsigned char *buffer){
    
    header->deserializeRequestHeader(buffer);

    deserialize_int_big_endian(buffer, &numFiles);

    for (int i = 0; i < numFiles; i++) {
        files->at(i).deserializeRequestFile(buffer);
    }
}

unsigned char * CreateRequest::serializeRequest(unsigned char *buffer){
    
    header->serializeRequestHeader(buffer);
    
    serialize_int_big_endian(buffer, numFiles);

    for (int i = 0; i < numFiles; i++) {
        buffer = files->at(i).serializeRequestFile(buffer);
    }
    return buffer; 
}
