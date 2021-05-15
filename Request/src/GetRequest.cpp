#include <GetRequest.hpp>

using namespace request;

int GetRequest::getRequestBodySize() const {
    return strlen(filepath) + 1;   
}

void GetRequest::deserializeRequestBody(unsigned char *buffer){
    
    header->deserializeRequestHeader(buffer);

    buffer = deserialize_char_array(buffer, filepath);
}

unsigned char * GetRequest::serializeRequestBody(unsigned char *buffer){
    
    buffer = header->serializeRequestHeader(buffer);
    
    buffer = serialize_char_array(buffer, filepath);
    
    return buffer; 
}

std::string GetRequest::GetBody() const {
    return "{ }";
}
