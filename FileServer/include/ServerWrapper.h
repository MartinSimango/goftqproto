
#pragma once
#include <stdbool.h>
#define READ_MODE 0
#define WRITE_MODE 1

#ifdef __cplusplus
extern "C" {
#endif

void* NewFileServer(int port, char * rootFolder);

void DestroyFileServer(void* fs);

void* StartServer(void* fs, int connections);

void* Accept(void* fs);

void* HandleClientRequest(void * fs);

void * IsServerRunning(void * fs);

void* CloseFileServer(void* fs);

#ifdef __cplusplus
}  // extern "C"
#endif
