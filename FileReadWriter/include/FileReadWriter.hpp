#pragma once
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <PacketConstants.h>
#include <stdio.h>
#include <FRWException.hpp>

class FileReadWriter
{
    
private:
    char filename[MAX_FILEPATH_LENGTH];
    bool mode, opened;
    int fd, fileSize;
    
    inline void openFileForReading() {         
        if ( (this->fd = open(this->filename, O_RDONLY) ) < 0) 
            throw new FRWException(FAILED_TO_OPEN_FILE_FOR_READING, this->filename);    
    }

    inline void openFileForWriting(bool create = false) {
        if (create) {
            createFileForWriting();
        }
        else if ( (this->fd = open(this->filename, O_WRONLY) ) < 0) {  
            throw new FRWException(FAILED_TO_OPEN_FILE_FOR_WRITING, this->filename);
        }
        opened = true;    
    }

    inline void createFileForWriting(){
        if (this->fileSize == -1)
            throw new FRWException(INVALID_FILE_SIZE, this->filename);

        // 0666 is to give all reading and writing permissions
        // TODO check why files arent being created with this permission
        if ( (this->fd = open(this->filename, O_CREAT | O_TRUNC | O_WRONLY, 0666) ) < 0) 
            throw new FRWException(FAILED_TO_OPEN_FILE_FOR_WRITING, this->filename);

        // resize the file to be the desired size of the incoming file being copied
        resizeFile();
        opened = true;    
    }

    inline void resizeFile() {
        if (ftruncate(this->fd, this->fileSize) < 0) {
            Close();
            throw new FRWException(FAILED_TO_RESIZE_FILE, this->filename);
        }
    }


    static inline unsigned char checkFileForRead(const char * filename) {
            if (access(filename, F_OK) == 0) {
                return access(filename, R_OK) == 0 ? OK : NO_READ_PERMISSIONS;
            }
            else {
                return FILE_NOT_FOUND;
            }
        }    

    static inline unsigned char checkFileForWrite(const char * filename) {
        if (access(filename, F_OK) == 0) {
            return access(filename, W_OK) == 0 ? OK : NO_WRITE_PERMISIONS;
        }
        return OK;
    }
            
     


public:
    FileReadWriter(char * filename, bool mode, int fileSize = -1): mode(mode), fileSize(fileSize), opened(false){
         strlcpy(this->filename, filename ,sizeof(this->filename));
    }

    ~FileReadWriter(){}

    // Open opens the file resource
    void Open(bool create = false);

    int WriteToFile(char * data, size_t number_of_bytes, int offset);

    int ReadFromFile(char * data, size_t number_of_bytes, int offset);

    // Closes closes the file resource
    void Close();

    const char * GetFileName() const;

    int GetFileSize() const;

    static unsigned char CheckFile(const char * filename, bool mode);

    static int GetFileSize(const char *filename);
};


