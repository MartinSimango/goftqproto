#include <ReadResponse.hpp>

using namespace response;

int ReadResponse::getResponseBodySize() const {
    return sizeof(numberOfBytesRead);
}

void ReadResponse::deserializeResponse(unsigned char *buffer){
    
    header->deserializeResponseHeader(buffer);

    buffer = deserialize_int_big_endian(buffer, &numberOfBytesRead);
    }

unsigned char * ReadResponse::serializeResponse(unsigned char *buffer){
    
    buffer = header->serializeResponseHeader(buffer);
    
    buffer = serialize_int_big_endian(buffer, numberOfBytesRead);

    return buffer; 

}
