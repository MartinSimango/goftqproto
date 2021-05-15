#include <Request.hpp>

using namespace request;

int Request::Write(){
    WriteHeader();
    WriteBody();
}

int Request::Read(){
    ReadHeader();
    ReadBody();
}

int Request::WriteBody() {

    int requestBodySize = getRequestBodySize();
    unsigned char buffer[requestBodySize]; 
    unsigned char *ptr; 

    ptr = serializeRequestBody(buffer);

    int bytes_written = write(fd, buffer, ptr - buffer);   

    if (bytes_written < 0) {
        throw new RequestException(FAILED_TO_WRITE_REQUEST, this->requestType);
    }
    
    return bytes_written;
}

int Request::ReadBody(){
   
    int requestBodySize = this->header->getRequestBodySize();

    unsigned char* buffer = new unsigned char[requestBodySize]; 

    int bytesRead;
    int totalBytesRead = 0;
    while ( (bytesRead = read(fd, buffer, requestBodySize) ) > 0 && totalBytesRead < requestBodySize) {
        buffer = (unsigned char *) (buffer + bytesRead);
        totalBytesRead += bytesRead;
    }
   
    
    delete buffer;

    if (bytesRead < 0) 
        throw new RequestException(FAILED_TO_READ_REQUEST, this->requestType);

    deserializeRequestBody(buffer);

    return totalBytesRead;
}


int Request::WriteHeader() {
    delete this->header;

    this->header = new RequestHeader(this->getRequestBodySize(), this->requestType);
    unsigned char buffer[this->header->getRequestHeaderSize()]; 
    unsigned char *ptr; 

    ptr = this->header->serializeRequestHeader(buffer);

    int bytes_written = write(fd, buffer, ptr - buffer); 

    if (bytes_written < 0) {
        throw new RequestException(FAILED_TO_WRITE_REQUEST_HEADER, this->requestType);
    }

    return bytes_written;
}

int Request::ReadHeader() {
    delete this->header;
    this->header = new RequestHeader(fd);
    
    return this->header->Read();
}