#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "serialize.h"


class FileReadWriter
{
private:
    char * filename;
    bool mode; // true if reading
    int fd;
    bool opened;
    int fileSize; //file size in megabytes
    
    inline int openFileForReading() { 
        if(access(filename, F_OK ) == 0 ) {
            return open(filename, O_RDONLY);
        } else {
            return -2; // file does not exist
        }
    }

    inline int openFileForWriting() {
        return open(filename, O_WRONLY | O_CREAT, 0666);
    }


public:
    FileReadWriter(char * filename, bool mode): filename(filename), mode(mode){ opened = false;}
    ~FileReadWriter();
    bool Open(){
        fd = (mode == READ) ? openFileForReading() : openFileForWriting();
        opened = (fd >= 0);
        return opened;
    }

    int WriteToFile(char * data,size_t number_of_bytes, int offset){
         if(!opened){
            return -2;
        }
        lseek (fd, offset, SEEK_CUR);       
        return write (fd, data, number_of_bytes);
    }
    int ReadFromFile(char * data,size_t number_of_bytes, int offset) {
        if(!opened){
            return -2;
        }
        lseek (fd, offset, SEEK_CUR);   
        return read(fd, data, number_of_bytes);
    }

    int Close(){
        if(opened) {
            opened = false;
            return close(fd);
        }
        return -2;
    }


};


