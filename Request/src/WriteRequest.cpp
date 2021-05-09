#include <WriteRequest.hpp>

using namespace request;

int WriteRequest::getRequestSize() const {
    return sizeof(offset) + sizeof(numberOfBytesToWrite) + strlen(data) + 1 + strlen(filepath) + 1 ; 
}

void WriteRequest::deserializeRequest(unsigned char *buffer){
    
    header->deserializeRequestHeader(buffer);

    buffer = deserialize_int_big_endian(buffer, &offset);
    buffer = deserialize_int_big_endian(buffer, &numberOfBytesToWrite); 
    buffer = deserialize_char_array(buffer, filepath);
    buffer = deserialize_char_array(buffer, data);

}

unsigned char * WriteRequest::serializeRequest(unsigned char *buffer){
    
    buffer = header->serializeRequestHeader(buffer);
    
    buffer = serialize_int_big_endian(buffer, offset);
    buffer = serialize_int_big_endian(buffer, numberOfBytesToWrite);
    buffer = serialize_char_array(buffer, filepath);    
    buffer = serialize_char_array(buffer, data);

    return buffer; 
    
  
}
