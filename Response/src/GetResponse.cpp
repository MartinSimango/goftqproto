#include <GetResponse.hpp>

using namespace response;

int GetResponse::getResponseBodySize() const {
    int fileSize = 0;
    for (int i = 0; i < numFiles; i++) {
        fileSize += files->at(i).getSize();
    }
    return fileSize;
}

void GetResponse::deserializeResponseBody(unsigned char *buffer){
    
    deserialize_int_big_endian(buffer, &numFiles);

    for (int i = 0; i < numFiles; i++) {
        buffer = files->at(i).deserializeRequestFile(buffer);
    }
}

unsigned char * GetResponse::serializeResponseBody(unsigned char *buffer){
        
    serialize_int_big_endian(buffer, numFiles);

    for (int i = 0; i < numFiles; i++) {
        buffer = files->at(i).serializeRequestFile(buffer);
    }
    return buffer; 
}

std::string GetResponse::GetBody() const {
    return "{ }";
}
