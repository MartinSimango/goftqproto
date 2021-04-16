
#include <FileReadWriterWrapper.h>
#include <FileReadWriter.hpp>


void * NewFileReadWriter(char * filename, bool mode, int fileSize = 0){
    auto frw = new FileReadWriter(filename, mode, fileSize);
    return frw;
}

// Utility function local to the bridge's implementation
FileReadWriter* AsFileReadWriter(void* frw) { 
    return reinterpret_cast<FileReadWriter*>(frw); 
}
void DestroyFileReadWriter(FileReadWriter* frw){
    AsFileReadWriter(frw)->~FileReadWriter();
}

bool Open(void* frw){
    return AsFileReadWriter(frw)->Open();
}
int WriteToFile(void* frw, char * data,size_t number_of_bytes, int offset){
    return AsFileReadWriter(frw)->WriteToFile(data, number_of_bytes, offset);
}
int ReadFromFile(void* frw, char * data,size_t number_of_bytes, int offset){
    return AsFileReadWriter(frw)->ReadFromFile(data, number_of_bytes, offset);
}
int Close(void *frw){
    return AsFileReadWriter(frw)->Close();
}

char * GetFileName(void *frw) {
    return AsFileReadWriter(frw)->getFileName();
}
