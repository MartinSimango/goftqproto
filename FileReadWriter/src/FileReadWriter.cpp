#include <FileReadWriter.hpp>
#include <stdio.h>

using namespace frw;

void FileReadWriter::Open(){
    if(opened){
        throw new FRWException(FAILED_TO_OPEN_FILE_ALREADY_OPEN, filename);
    }
    (mode == Mode::READ) ? openFileForReading() : openFileForWriting();
    opened = true;
}

int FileReadWriter::WriteToFile(char * data, size_t number_of_bytes, int offset){
    if (!opened) 
        throw new FRWException(FAILED_TO_WRITE_FILE_NOT_OPEN, this->filename);
    
    int bytes_read;
    if (lseek (this->fd, offset, SEEK_CUR) < 0 || (bytes_read = write(this->fd, data, number_of_bytes) ) < 0) 
        throw new FRWException(FAILED_TO_WRITE_TO_FILE, this->filename);

    return bytes_read;
}

int FileReadWriter::ReadFromFile(char * data, size_t number_of_bytes, int offset) {
    if (!opened)
        throw new FRWException(FAILED_TO_READ_FILE_NOT_OPEN, filename);
    
    int bytes_read;

    if (lseek (fd, offset, SEEK_CUR) < 0 || ( bytes_read = read(fd, data, number_of_bytes) ) < 0)  {
        throw new FRWException(FAILED_TO_READ_FROM_FILE, filename);
    }
    return bytes_read;
}

void FileReadWriter::Close(){
    if (!opened)
        throw new FRWException(FAILED_TO_CLOSE_FILE_NOT_OPEN, filename);
    if (close(fd) < 0)
        throw new FRWException(FAILED_TO_CLOSE_FILE, filename);
    opened = false;
}

const char * FileReadWriter::GetFileName() const {
    return filename;
}

int FileReadWriter::GetFileSize() const {
    return fileSize;
}

int FileReadWriter::GetFileDescriptor() const {
    if (!opened)
        throw new FRWException(FAILED_TO_GET_FD_NOT_OPEN, filename);
    return fd;
}


ResponseStatus::Type FileReadWriter::CheckFile(const char * filename, Mode::Type mode) {
      return (mode == Mode::READ) ? checkFileForRead(filename)
                            : checkFileForWrite(filename);
}

int FileReadWriter::GetFileSize(const char * filename) {
    struct stat st;
    if(stat(filename, &st) != 0) 
        throw new FRWException(FAILED_TO_GET_FILE_SIZE, filename);
    
    return st.st_size;
}
//CreateFile creates a file named filename of size fileSize in bytes
void FileReadWriter::CreateFile(char *filename, int fileSize) {
    if (fileSize < 0)
        throw new FRWException(INVALID_FILE_SIZE, filename);

    // 0666 is to give all reading and writing permissions
    // TODO check why files arent being created with this permission
    int fd;
    if ( (fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666) ) < 0) 
        throw new FRWException(FAILED_TO_CREATE_FILE, filename);

    // resize the file to be the desired size of the incoming file being copied
    if (ftruncate(fd, fileSize) < 0) {
        if (close(fd) < 0){
            throw new FRWException(FAILED_TO_CLOSE_FILE, filename);
        }
        throw new FRWException(FAILED_TO_RESIZE_FILE, filename);
    }
}
