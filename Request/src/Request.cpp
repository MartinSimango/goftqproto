#include <Request.hpp>

using namespace request;

int Request::Write(){
    return WriteHeader() + WriteBody();
}

int Request::Read(){
   return ReadHeader() + ReadBody();
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

    unsigned char tmp_buffer[requestBodySize];
    unsigned char* buffer = new unsigned char[requestBodySize]; 

    int bytesRead;
    int totalBytesRead = 0;
    while (totalBytesRead < requestBodySize && (bytesRead = read(fd, tmp_buffer, requestBodySize) ) > 0) {
        for (int i =0; i< bytesRead ;i++){
            buffer[totalBytesRead + i] = tmp_buffer[i];
        }
        totalBytesRead += bytesRead;
    }
   

    if (bytesRead < 0)  {
        throw new RequestException(FAILED_TO_READ_REQUEST, this->requestType);
        delete [] buffer;
    }
    deserializeRequestBody(buffer);
    delete [] buffer;

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