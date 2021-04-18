#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <PacketConstants.h>
#include <stdio.h>

class FileReadWriter
{
    
private:
    char filename[MAX_FILEPATH_LENGTH];
    bool mode; // true if reading
    int fd;
    bool opened;
    int fileSize; //file size in megabytes TODO use this
    
    inline int openFileForReading() { 
        // file is assumed exist (check by Server)
        return open(filename, O_RDONLY);
    }

    inline int openFileForWriting() {

        int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY , 0666); //give read write permissions to all users
        if (fileSize > 0) {
            createEmptyFileOfSize(this->filename, this->fileSize);
        }
        return fd;
    }


public:
    FileReadWriter(char * filename, bool mode, int fileSize = 0): mode(mode){
         strlcpy(this->filename, filename ,sizeof(this->filename));
         this->fileSize = fileSize;
         opened = false;
    }

    ~FileReadWriter(){}

    // Open opens the file resource
    bool Open();

    int WriteToFile(char * data,size_t number_of_bytes, int offset);

    int ReadFromFile(char * data,size_t number_of_bytes, int offset);

    // Closes closes the file resource
    int Close();

    const char * getFileName() const;

    // TPDP change this to a priveate method
    static int createEmptyFileOfSize(char * filename, int size);
    
    static int getFileSize(const char * filename);

};


