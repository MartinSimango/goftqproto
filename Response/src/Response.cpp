#include <Response.hpp>

using namespace response;

int Response::WriteResponse() {
            
    int packetBodyByteSize = getResponseBodySize();

    header = new ResponseHeader(packetBodyByteSize, this->responseType, this->header->getStatus());
    
    unsigned char buffer[packetBodyByteSize + header->getResponseHeaderSize()]; 
    unsigned char *ptr; 

    ptr = serializeResponse(buffer);

    int bytes_written = write(fd, buffer, ptr - buffer);   

    if (bytes_written < 0) {
        throw new ResponseException(FAILED_TO_WRITE_RESPONSE, this->responseType);
    }
    
    return bytes_written;
}

int Response::ReadResponse(){

    //read in the header
    header = new ResponseHeader();
    unsigned char headerBuffer[header->getResponseHeaderSize()];
    header->deserializeResponseHeader(headerBuffer);

    int packetBodyByteSize = header->getResponseBodySize();

    unsigned char* buffer = new unsigned char[packetBodyByteSize]; 

    int bytesRead;
    int totalBytesRead = 0;
    while ( (bytesRead = read(fd, buffer, packetBodyByteSize) ) > 0 && totalBytesRead < packetBodyByteSize ) {
        buffer = (unsigned char *) (buffer + bytesRead);
        totalBytesRead += bytesRead;
    }
   
    
    delete buffer;

    if (bytesRead < 0) 
        throw new ResponseException(FAILED_TO_READ_FROM_RESPONSE, this->responseType);

    deserializeResponse(buffer);

    return totalBytesRead;
}


