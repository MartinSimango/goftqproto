#include <RequestHeader.hpp>
#include <RequestException.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace request;

int RequestHeader::getRequestHeaderSize(){
    return sizeof(requestBodySize) + sizeof(requestType);
}

unsigned char * RequestHeader::serializeRequestHeader(unsigned char *buffer) {
    buffer = serialize_int_big_endian(buffer, requestBodySize);
    buffer = serialize_int_big_endian(buffer, requestType);
    return buffer;
}

void RequestHeader::deserializeRequestHeader(unsigned char *buffer) {
    buffer = deserialize_int_big_endian(buffer, &requestBodySize);
    buffer = deserialize_int_big_endian(buffer, (int*)&requestType); 
}

int RequestHeader::getRequestBodySize() const {
    return requestBodySize;
}

int RequestHeader::Read() {
    
    unsigned char buffer[getRequestHeaderSize()];
    int bytes_read = read(fd, buffer, getRequestHeaderSize()); //todo use while to ensure all data is read

    if (bytes_read < 0) { 
        throw new RequestException(FAILED_TO_READ_REQUEST_HEADER, this->requestType);
    }
    deserializeRequestHeader(buffer);

    return bytes_read;
}
