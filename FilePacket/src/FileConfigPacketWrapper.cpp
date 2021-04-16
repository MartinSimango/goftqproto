#include <FileConfigPacketWrapper.h>
#include <FileConfigPacket.hpp>

using namespace packet;

FileConfigPacket* AsFileConfigPacket(void* fcp) { 
    return reinterpret_cast<FileConfigPacket*>(fcp); 
}


void* NewFileConfigPacket(int fd){
    auto fpc = new FileConfigPacket(fd);
    return fpc;
}

void* NewFileConfigPacketWithOffsetAndReadytes(int fd, int offset, int numberOfBytesToRead){
    auto fpc = new FileConfigPacket(fd, offset, numberOfBytesToRead);
    return fpc;

}

void DestroyFileConfigPacket(void* fcp){
    AsFileConfigPacket(fcp)->~FileConfigPacket();
}

int GetReadPacketSize(void* fcp){
    return AsFileConfigPacket(fcp)->getReadPacketSize();
}

void DeserializePacket(void* fcp, unsigned char *buffer){
    return AsFileConfigPacket(fcp)->deserializePacket(buffer);

}

unsigned char * SerializePacket(void* fcp, unsigned char *buffer){
    return AsFileConfigPacket(fcp)->serializePacket(buffer);
}