#pragma once
#ifdef __cplusplus
extern "C" {
#endif

void* NewFileReadWriter(char * filename, bool mode, int fileSize);
void DestroyFileReadWriter(void* frw);
bool OpenFile(void* frw);
int WriteToFile(void* frw,char * data,int number_of_bytes, int offset);
int ReadFromFile(void* frw,char * data,int number_of_bytes, int offset);
// Closes closes the file resource
int CloseFile(void* frw);
char * GetFileName(void* frw);

#ifdef __cplusplus
}  // extern "C"
#endif