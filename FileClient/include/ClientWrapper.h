
#pragma once
#include <stdbool.h>

#define READ_MODE 0
#define WRITE_MODE 1

#ifdef __cplusplus
extern "C" {
#endif


void* NewFileClient();

void DestroyFileClient(void* fc);

// Connect connects the client to the specific server specified by the ServerPort 
void * Connect(void* fc,char * serverAddress, int port);

void * SendCreateRequest(void* fc, char * filenames[], int fileSizes[], int numFiles);

void * SendGetRequest(void* fc, char * filepath);

void * SendReadRequest(void* fc, int numberOfBytesToRead, int offset, char *readFile, char * writeFile);

void * SendWriteRequest(void* fc, int numberOfBytesToWrite, int offset, char *readFile, char * writeFile);

// Close closes the connection to the server, returns false upon failure
void Close();

// CloseFileClient closes the connection to the server, returns false upon failure
void * CloseFileClient(void* fc);


#ifdef __cplusplus
}  // extern "C"
#endif
