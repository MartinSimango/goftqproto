#include <Response.hpp>

using namespace response;

int Response::Write() {
    WriteHeader();
    WriteBody();
}

int Response::Read() {
    ReadHeader();
    ReadBody();
}

int Response::WriteBody() {
            
        
    int responseBodySize = getResponseBodySize();
    
    unsigned char buffer[responseBodySize]; 
    unsigned char *ptr; 

    ptr = serializeResponseBody(buffer);

    int bytes_written = write(fd, buffer, ptr - buffer);   //todo loop write to ensure all bytes are written

    if (bytes_written < 0) {
        throw new ResponseException(FAILED_TO_WRITE_RESPONSE, this->responseType);
    }
    
    return bytes_written;
}

int Response::ReadBody(){
    
    int packetBodyByteSize = this->header->getResponseBodySize();

    unsigned char* buffer = new unsigned char[packetBodyByteSize]; 

    int bytesRead;
    int totalBytesRead = 0;
    while ( (bytesRead = read(fd, buffer, packetBodyByteSize) ) > 0 && totalBytesRead < packetBodyByteSize ) {
        buffer = (unsigned char *) (buffer + bytesRead);
        totalBytesRead += bytesRead;
    }
   
    
    delete buffer;

    if (bytesRead < 0) 
        throw new ResponseException(FAILED_TO_READ_RESPONSE, this->responseType);

    deserializeResponseBody(buffer);

    return totalBytesRead;
}

int Response::WriteHeader() {
    delete this->header;

    this->header = new ResponseHeader(this->getResponseBodySize(), this->responseType, this->status);
    unsigned char buffer[this->header->getResponseHeaderSize()]; 
    unsigned char *ptr; 

    ptr = this->header->serializeResponseHeader(buffer);

    int bytes_written = write(fd, buffer, ptr - buffer); 

    if (bytes_written < 0) {
        throw new ResponseException(FAILED_TO_WRITE_RESPONSE_HEADER, this->responseType);
    }

    return bytes_written;
}

int Response::ReadHeader() {
    delete this->header;

    this->header = new ResponseHeader();
    unsigned char buffer[header->getResponseHeaderSize()];

    int bytes_read = read(fd, buffer, header->getResponseHeaderSize()); //todo use while to ensure all data is read

    if (bytes_read < 0) { 
        throw new ResponseException(FAILED_TO_READ_RESPONSE_HEADER, this->responseType);
    }
    header->deserializeResponseHeader(buffer);

    return bytes_read;
}



