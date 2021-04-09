#pragma once

#define KILOBYTE 1024
#define MEGABYTE 1024*1024
#define GIGABYTE 1024*1024*1024
#define MAX_FILEPATH_LENGTH 100
#define MAX_BUFFER_SIZE MEGABYTE

//packet types
#define PACKET 0
#define FILE_PACKET 1
#define FILE_CONFIG_PACKET 2
#define REQUEST_PACKET 3
#define RESPONSE_PACKET 4

//statuses
#define OK  0
#define FILE_NOT_FOUND 1
#define NO_WRITE_PERMISIONS 2
#define NO_READ_PERMISSIONS 3

//Modes
#define WRITE 0
#define READ 1