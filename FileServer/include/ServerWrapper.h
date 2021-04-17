
#pragma once
#include <stdbool.h>
#include <PacketConstants.h>
#ifdef __cplusplus
extern "C" {
#endif

void* NewFileServer(int port);

void DestroyFileServer(void* fs);

bool StartServer(void* fs, int connections);

bool Accept(void* fs);

bool Close(void* fs);

const char * GetErrorMessage(void* fs);

#ifdef __cplusplus
}  // extern "C"
#endif
