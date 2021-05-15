#include <ReadResponse.hpp>

using namespace response;

int ReadResponse::getResponseBodySize() const {
    return sizeof(numberOfBytesRead) + strlen(data) + 1;
}

void ReadResponse::deserializeResponseBody(unsigned char *buffer){    
    buffer = deserialize_int_big_endian(buffer, &numberOfBytesRead);
    buffer = deserialize_char_array(buffer, data);
}

unsigned char * ReadResponse::serializeResponseBody(unsigned char *buffer){
        
    buffer = serialize_int_big_endian(buffer, numberOfBytesRead);
    buffer = serialize_char_array(buffer, data);
    
    return buffer; 
}

std::string ReadResponse::GetBody() const {
    return "{ }";
}
