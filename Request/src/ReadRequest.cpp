#include <ReadRequest.hpp>

using namespace request;

int ReadRequest::getRequestBodySize() const {
    return sizeof(offset) + sizeof(numberOfBytesToRead) + strlen(filename) + 1 ; 
}

void ReadRequest::deserializeRequestBody(unsigned char *buffer){
    
    header->deserializeRequestHeader(buffer);

    buffer = deserialize_int_big_endian(buffer, &offset);
    buffer = deserialize_int_big_endian(buffer, &numberOfBytesToRead); 
    buffer = deserialize_char_array(buffer, filename);
    }

unsigned char * ReadRequest::serializeRequestBody(unsigned char *buffer){
    
    buffer = header->serializeRequestHeader(buffer);
    
    buffer = serialize_int_big_endian(buffer, offset);
    buffer = serialize_int_big_endian(buffer, numberOfBytesToRead);
    buffer = serialize_char_array(buffer, filename);

    return buffer; 
}

std::string ReadRequest::GetBody() const {
    return "{ }";
}
