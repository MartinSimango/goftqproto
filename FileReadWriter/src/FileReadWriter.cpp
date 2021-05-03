#include <PacketConstants.h>
#include <FileReadWriter.hpp>
#include <stdio.h>

void FileReadWriter::Open(bool create){
    (mode == READ) ? openFileForReading() : openFileForWriting(create);
    opened = true;
}

int FileReadWriter::WriteToFile(char * data, size_t number_of_bytes, int offset){
    if (!opened) 
        throw new FRWException(FAILED_TO_WRITE_FILE_NOT_OPEN, filename);
    
    int bytes_read;
    if (lseek (fd, offset, SEEK_CUR) < 0 || (bytes_read = write(fd, data, number_of_bytes) ) < 0) 
        throw new FRWException(FAILED_TO_WRITE_TO_FILE, filename);

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
}

const char * FileReadWriter::GetFileName() const {
    return filename;
}

int FileReadWriter::GetFileSize() const {
    return fileSize;
}

unsigned char FileReadWriter::CheckFile(const char * filename, bool mode) {
      return (mode == READ) ? checkFileForRead(filename)
                            : checkFileForWrite(filename);
}

int FileReadWriter::GetFileSize(const char * filename) {
    struct stat st;
    if(stat(filename, &st) != 0) 
        throw new FRWException(FAILED_TO_GET_FILE_SIZE, filename);
    
    return st.st_size;
}