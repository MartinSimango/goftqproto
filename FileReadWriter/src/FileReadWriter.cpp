#include <PacketConstants.h>
#include <FileReadWriter.hpp>
#include <stdio.h>

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

const char * FileReadWriter::getFileName() const {
    return filename;
}


int FileReadWriter::createEmptyFileOfSize(char * filename, int size){
    FILE *fp = fopen(filename, "w");
    if(!fp) {
        return -1;
    }
    ftruncate(fileno(fp), size);

    return fclose(fp);
}

int FileReadWriter::getFileSize(const char * filename) {
    struct stat st;
    if(stat(filename, &st) != 0) {
        return 0;
    }
    return st.st_size;
}
