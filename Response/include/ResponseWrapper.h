#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct CreateResponseStruct {
        char ** filenames;
        int * fileSizes;
        int numFiles;
} CreateResponseStruct;

void DestroyCreateResponse(void *cr);

CreateResponseStruct GetCreateResponse(void *cr);
// char ** CreateResponse_GetFilenames(void *cr);

// int * CreateResponseGetFileSizes(void *cr);

// int CreateResponse_GetNumFiles(void *cr);

#ifdef __cplusplus
}  // extern "C"
#endif
