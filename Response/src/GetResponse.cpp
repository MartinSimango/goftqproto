#include <GetResponse.hpp>

using namespace response;

int GetResponse::getResponseBodySize() const {
    int fileSize = 0;
    for (int i = 0; i < numFiles; i++) {
        fileSize += files->at(i).getSize();
    }
    return fileSize;
}

void GetResponse::deserializeResponse(unsigned char *buffer){
    
    header->deserializeResponseHeader(buffer);

    deserialize_int_big_endian(buffer, &numFiles);

    for (int i = 0; i < numFiles; i++) {
        files->at(i).deserializeRequestFile(buffer);
    }
}

unsigned char * GetResponse::serializeResponse(unsigned char *buffer){
    
    header->serializeResponseHeader(buffer);
    
    serialize_int_big_endian(buffer, numFiles);

    for (int i = 0; i < numFiles; i++) {
        buffer = files->at(i).serializeRequestFile(buffer);
    }
    return buffer; 
}
