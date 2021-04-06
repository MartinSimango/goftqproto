#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>


class FileReadWriter
{
    
private:
    char * filename;
    bool mode; // true if reading
    int fd;
    bool opened;
    int fileSize; //file size in megabytes
    
    inline int openFileForReading() { 
        // file is assumed exist (check by Server)
        return open(filename, O_RDONLY);
    }

    inline int openFileForWriting() {
        return open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666); //give read write permissions to all users
    }


public:
    FileReadWriter(char * filename, bool mode): filename(filename), mode(mode){ opened = false;}

    // Open opens the file resource
    bool Open();

    int WriteToFile(char * data,size_t number_of_bytes, int offset);

    int ReadFromFile(char * data,size_t number_of_bytes, int offset);

    // Closes closes the file resource
    int Close();
};


