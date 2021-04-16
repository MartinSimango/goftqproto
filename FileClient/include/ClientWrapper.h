
#pragma once
#include <stdbool.h>
#include <PacketConstants.h>
#ifdef __cplusplus
extern "C" {
#endif

void* NewFileClient(int mode, char * requestFileName, char * filename);
void DestroyFileClient(void* fc);
// Connect connects the client to the specific server specified by the ServerPort 
// returns false if connect failed and errorMessage is set
bool Connect(void* fc,char * serverAddress, int port);
// Process either reads or writes to the server depending on what mode the FileClient is in
// returns the number of bits written or read to the server depending on the mode
int Process(void* fc,int offset, int numberOfBytesRead);
// GetErrorMessge returns the errorMessage 
const char * GetErrorMessage(void* fc);
// Close closes the connection to the server, returns false upon failure
bool Close(void* fc);

#ifdef __cplusplus
}  // extern "C"
#endif
