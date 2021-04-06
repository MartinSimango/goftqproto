#include "FileReadWriter.hpp"
#include "../Packet/RequestPacket.hpp"

bool FileReadWriter::Open(){
    fd = (mode == READ) ? openFileForReading() : openFileForWriting();
    opened = (fd >= 0);
    return opened;
}

int FileReadWriter::WriteToFile(char * data,size_t number_of_bytes, int offset){
        if(!opened){
        return -2;
    }
    lseek (fd, offset, SEEK_CUR);       
    return write (fd, data, number_of_bytes);
}
int FileReadWriter::ReadFromFile(char * data,size_t number_of_bytes, int offset) {
    if(!opened){
        return -2;
    }
    lseek (fd, offset, SEEK_CUR);   
    return read(fd, data, number_of_bytes);
}

int FileReadWriter::Close(){
    if(opened) {
        opened = false;
        return close(fd);
    }
    return -2;
}
