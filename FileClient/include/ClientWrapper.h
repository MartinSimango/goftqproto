
#pragma once
#include <stdbool.h>
#include <PacketConstants.h>

#ifdef __cplusplus
extern "C" {
#endif


void* NewFileClient(int mode, char * requestFileName, char * filename);

void DestroyFileClient(void* fc);

// Connect connects the client to the specific server specified by the ServerPort 
void * Connect(void* fc,char * serverAddress, int port, bool create);
// Process either reads or writes to the server depending on what mode the FileClient is in
// returns the number of bits written or read to the server depending on the mode
void * Process(void* fc,int offset, int numberOfBytesRead);

void * GetFileClientFileSize(void *fc);

// CloseFileClient closes the connection to the server, returns false upon failure
void * CloseFileClient(void* fc);


#ifdef __cplusplus
}  // extern "C"
#endif
