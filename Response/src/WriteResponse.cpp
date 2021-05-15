#include <WriteResponse.hpp>

using namespace response;

int WriteResponse::getResponseBodySize() const {
    return sizeof(numberOfBytesWritten);
}

void WriteResponse::deserializeResponseBody(unsigned char *buffer){
    
    buffer = deserialize_int_big_endian(buffer, &numberOfBytesWritten);
    
}

unsigned char * WriteResponse::serializeResponseBody(unsigned char *buffer){
        
    buffer = serialize_int_big_endian(buffer, numberOfBytesWritten);

    return buffer; 
}

std::string WriteResponse::GetBody() const {
    return "{ }";
}

