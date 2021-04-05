#ifndef _SERIALIZE_
#define _SERIALIZE_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ostream>

#define WRITE 0
#define READ 1
#define MEGABYTE 1024*1024
#define FILEPATH_MAX_LENGTH 100
#define TRANSFER_DATA_SIZE MEGABYTE

#define OK  0
#define FILE_NOT_FOUND 1
#define PERMISION_DENIED 2
//statuses 

// TODO seperate different functions to seperate files as file is getting quite large

// TODO: reorder struct memebers to decrease file size
// TODO: make an absract class/struct called Packet that has one abstract method called getType which just returns a constant of
// what class it is
struct FilePacket {

    int bytesRead; // number of bytes read 
    char data[TRANSFER_DATA_SIZE]; //data to be written

    FilePacket(){}
    FilePacket(char * data, int offset, int bytesRead) {
        strcpy(this->data, data);
        this->bytesRead = bytesRead;
    }
};
    

struct FileReadPacket {
    int offset; // where to start reading
    int numberOfBytesToRead; //max number of bytes to read
};

struct RequestPacket {
    bool mode;
    char filename[FILEPATH_MAX_LENGTH];
 
};

struct ResponsePacket {
    unsigned char status;
};


//Below functions are based from https://stackoverflow.com/questions/1577161/passing-a-structure-through-sockets-in-c


inline unsigned char * serialize_int_big_endian(unsigned char *buffer, int value)
{
  /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  buffer[0] = value >> 24; // get first byte of int
  buffer[1] = value >> 16; // get second byte of int
  buffer[2] = value >> 8;  // get third byte of int
  buffer[3] = value;    // get fouth byte of int
  return buffer + 4;
}

inline unsigned char * serialize_int_little_endian(unsigned char *buffer, int value)
{
  /* Write little-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  buffer[0] = value;
  buffer[1] = value >> 8;
  buffer[2] = value >> 16; // get fir byte of int
  buffer[3] = value >> 24; // get second byte of int
  return buffer + 4;
}


inline unsigned char * serialize_char_array(unsigned char *buffer, char * value)
{
    int value_len = strlen(value)+1; // +1 to include '\0' character too 

    for (int i = 0; i < value_len; i++){
    
        buffer[i] = value[i];
    }
    return buffer + value_len;
}


inline unsigned char * serialize_char(unsigned char *buffer, char value)
{
    buffer[0] = value;
    return buffer + 1;
}


inline unsigned char * deserialize_int_big_endian(unsigned char *buffer, int *value)
{   
    for (int i = 0; i < 4; i++) {
       *value += pow(2, 3-i) * buffer[i];
    }
    return buffer + 4;

}
inline unsigned char * deserialize_int_little_endian(unsigned char *buffer, int *value){

    for (int i = 0; i < 4; i++) {
       *value += pow(2, i) * buffer[i];
    }
    return buffer + 4;
    
}

inline unsigned char * deserialize_char_array(unsigned char *buffer, char * value)
{
    int i = 0;

    while(buffer[i] != '\0'){
        value[i] = buffer[i];
        i++;
    }

    return buffer + (i + 1);
}


inline unsigned char * deserialize_char(unsigned char *buffer, char* value)
{
    *value = buffer[0];
    return buffer + 1;
}


inline unsigned char * serialize_file_packet(unsigned char *buffer, struct FilePacket * packet)
{
  buffer = serialize_int_big_endian(buffer, packet->bytesRead);
  buffer = serialize_char_array(buffer, packet->data);

  return buffer; //this is a pointer at the end of buffer
}

inline unsigned char * deserialize_file_packet(unsigned char *buffer, struct FilePacket * packet) {
    //get the first four bytes of the buffer
    
  buffer = deserialize_int_big_endian(buffer, &(packet->bytesRead));
  buffer = deserialize_char_array(buffer, packet->data);

  return buffer;

}

inline unsigned char * serialize_request_packet(unsigned char *buffer, struct RequestPacket * packet)
{
  buffer = serialize_char(buffer, packet->mode); //returns a pointer after the end of the before
  buffer = serialize_char_array(buffer, packet->filename);

  return buffer; //this is a pointer at the end of buffer
}

inline unsigned char * serialize_response_packet(unsigned char *buffer, struct ResponsePacket * packet)
{
  buffer = serialize_char(buffer, packet->status); //returns a pointer after the end of the before

  return buffer; //this is a pointer at the end of buffer
}

inline unsigned char * serialize_file_read_packet(unsigned char *buffer, struct FileReadPacket * packet){
  
  buffer = serialize_int_big_endian(buffer, packet->offset);
  buffer = serialize_int_big_endian(buffer, packet->numberOfBytesToRead);
  return buffer;
  
}

inline unsigned char * deserialize_request_packet(unsigned char *buffer, struct RequestPacket * packet)
{
  buffer = deserialize_char(buffer,(char *) &(packet->mode)); 
  buffer = deserialize_char_array(buffer, packet->filename);

  return buffer; //this is a pointer at the end of buffer
}

inline unsigned char * deserialize_response_packet(unsigned char *buffer, struct ResponsePacket * packet)
{
  buffer = deserialize_char(buffer, (char*) &(packet->status)); 

  return buffer; //this is a pointer at the end of buffer
}

inline unsigned char * deserialize_file_read_packet(unsigned char *buffer, struct FileReadPacket * packet){
  
  buffer = deserialize_int_big_endian(buffer, &(packet->offset));
  buffer = deserialize_int_big_endian(buffer, &(packet->numberOfBytesToRead));
  return buffer;
  
}

inline int get_size_of_request_packet(struct RequestPacket * packet){
    return sizeof(packet->mode) + strlen(packet->filename) + 1; // +1 to accomodate for '\0' character
}


inline int get_size_of_file_packet(struct FilePacket * packet){
    return sizeof(packet->bytesRead) +
           strlen(packet->data) + 1; // +1 to accomodate for '\0' character
}

inline int get_size_of_file_read_packet(struct FileReadPacket * packet){
    return sizeof(packet->offset) + sizeof(packet->numberOfBytesToRead);
}

// TODO generalize these read and write functions so as to take in a (void *) struct in order to use one function for reading/writing

inline int write_serialized_file_packet(int fd, struct FilePacket * packet) {
    
    unsigned char buffer[get_size_of_file_packet(packet)];  //buffer will point to the start of the array of data bytes to be written and is where data is stored
    unsigned char *ptr; //ptr will point to the end of the array of data bytes to be written 

    ptr = serialize_file_packet(buffer, packet);

    return write(fd, buffer, ptr - buffer);   

}

inline int write_serialized_file_read_packet(int fd, struct FileReadPacket * packet){

    unsigned char buffer[get_size_of_file_read_packet(packet)]; 
    unsigned char *ptr; 

    ptr = serialize_file_read_packet(buffer, packet);

    return write(fd, buffer, ptr - buffer);   
}

// read_and_deserialize_file_packet reads from the file descriptor fd and des
inline int read_and_deserialize_file_packet(int fd, struct FilePacket * packet) {
    
    unsigned char buffer[TRANSFER_DATA_SIZE];  //buffer will point to the start of the array of data bytes to be written and is where data is stored
    unsigned char *ptr; //ptr will point to the end of the array of data bytes to be written 

    int bytesRead = read(fd, buffer, sizeof(buffer));
    
    deserialize_file_packet(buffer, packet);
    return bytesRead;
}

// read_serialized_file_packet reads from the file descriptor fd and des
inline int read_and_deserialize_file_read_packet(int fd, struct FileReadPacket * packet) {
    
    unsigned char buffer[get_size_of_file_read_packet(packet)];  //buffer will point to the start of the array of data bytes to be written and is where data is stored
    unsigned char *ptr; //ptr will point to the end of the array of data bytes to be written 

    int bytesRead = read(fd, buffer, sizeof(buffer));
    
    deserialize_file_read_packet(buffer, packet);
    return bytesRead;
}

// inline int write_request_packet

// // unsigned char buffer[get_size_of_request_packet(&requestPacket)];
// //             unsigned char *ptr;

// //             serialize_request_packet(buffer ,&requestPacket);
// //             if (write_serialized_data(sockfd, buffer, ptr) < 0) {
// //                 return false;
// //             }

#endif