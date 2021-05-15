#include <Response.hpp>

using namespace response;

int Response::Write() {

    return WriteHeader() + WriteBody();
}

int Response::Read() {
    return ReadHeader() + ReadBody();
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
        std::cout << "WTF body" << std::endl;

    int responseBodySize = this->header->getResponseBodySize();

    unsigned char tmp_buffer[responseBodySize];
    unsigned char* buffer = new unsigned char[responseBodySize]; 

    int bytesRead;
    int totalBytesRead = 0;
            std::cout << "WTF OK" << std::endl;

    while (totalBytesRead < responseBodySize && (bytesRead = read(fd, tmp_buffer, responseBodySize) ) > 0) {
            std::cout << "WTF OK please" << totalBytesRead  << " "<< bytesRead<< std::endl;

        for (int i =0; i< bytesRead ;i++){
            buffer[totalBytesRead + i] = tmp_buffer[i];
        }
        totalBytesRead += bytesRead;

    }
        std::cout << "WTF OK please at the end" << totalBytesRead  << " "<< bytesRead<< std::endl;



    if (bytesRead < 0) {
        throw new ResponseException(FAILED_TO_READ_RESPONSE, this->responseType);
        delete [] buffer;
    }

    deserializeResponseBody(buffer);
    std::cout << "WTF OK please atSDF " << std::endl; 

    delete [] buffer;

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
    
            std::cout << "FILENUM?: frepposne the end" << header->getResponseBodySize() << std::endl;

    return bytes_read;
}



