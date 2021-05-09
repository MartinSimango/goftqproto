#include <Request.hpp>

using namespace request;

int Request::WriteRequest() {
            
    int packetBodyByteSize = getRequestSize();

    header = new RequestHeader(packetBodyByteSize, this->requestType);
    
    unsigned char buffer[packetBodyByteSize + header->getRequestHeaderSize()]; 
    unsigned char *ptr; 

    ptr = serializeRequest(buffer);

    int bytes_written = write(fd, buffer, ptr - buffer);   

    if (bytes_written < 0) {
        throw new RequestException(FAILED_TO_WRITE_REQUEST, this->requestType);
    }
    
    return bytes_written;
}

int Request::ReadRequest(){

    //read in the header
    header = new RequestHeader();
    unsigned char headerBuffer[header->getRequestHeaderSize()];
    header->deserializeRequestHeader(headerBuffer);

    int packetBodyByteSize = header->getRequestBodySize();

    unsigned char* buffer = new unsigned char[packetBodyByteSize]; 

    int bytesRead;
    int totalBytesRead = 0;
    while ( (bytesRead = read(fd, buffer, packetBodyByteSize) ) > 0 && totalBytesRead < packetBodyByteSize ) {
        buffer = (unsigned char *) (buffer + bytesRead);
        totalBytesRead += bytesRead;
    }
   
    
    delete buffer;

    if (bytesRead < 0) 
        throw new RequestException(FAILED_TO_READ_FROM_REQUEST, this->requestType);

    deserializeRequest(buffer);

    return totalBytesRead;
}


