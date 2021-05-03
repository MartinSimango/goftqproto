
#pragma once
#include <stdbool.h>
#include <PacketConstants.h>

#ifdef __cplusplus
extern "C" {
#endif

void* NewFileServer(int port, char * rootFolder);

void DestroyFileServer(void* fs);

void* StartServer(void* fs, int connections);

void* Accept(void* fs);

void * GetFileServerFileSize(void *fs);

void* CloseFileServer(void* fs);

#ifdef __cplusplus
}  // extern "C"
#endif
