#include <WriteResponse.hpp>

using namespace response;

int WriteResponse::getResponseBodySize() const {
    return sizeof(numberOfBytesWritten);
}

void WriteResponse::deserializeResponse(unsigned char *buffer){
    
    header->deserializeResponseHeader(buffer);

    buffer = deserialize_int_big_endian(buffer, &numberOfBytesWritten);
    }

unsigned char * WriteResponse::serializeResponse(unsigned char *buffer){
    
    buffer = header->serializeResponseHeader(buffer);
    
    buffer = serialize_int_big_endian(buffer, numberOfBytesWritten);

    return buffer; 

}
