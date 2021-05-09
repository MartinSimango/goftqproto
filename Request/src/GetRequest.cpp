#include <GetRequest.hpp>

using namespace request;

int GetRequest::getRequestSize() const {
    return strlen(filepath) + 1;   
}

void GetRequest::deserializeRequest(unsigned char *buffer){
    
    header->deserializeRequestHeader(buffer);

    buffer = deserialize_char_array(buffer, filepath);
}

unsigned char * GetRequest::serializeRequest(unsigned char *buffer){
    
    buffer = header->serializeRequestHeader(buffer);
    
    buffer = serialize_char_array(buffer, filepath);
    
    return buffer; 
    
}
