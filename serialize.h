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


// TODO: reorder struct memebers to decrease file size
struct FilePacket {

    int offset; // where to start writing in the file
    int bytes_rw; // number of bytes read or written TODO might just rename to bytes read
    bool mode; 
    char filename[FILEPATH_MAX_LENGTH]; //file 
    char data[TRANSFER_DATA_SIZE]; //data to be written

};

struct FileReadWritePacket {
    int offset; // where to start reading
    int bytesToReadWrite; //max number of bytes to read or write
    char filename[FILEPATH_MAX_LENGTH]; //file to read

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
  buffer = serialize_int_big_endian(buffer, packet->offset); //returns a pointer after the end of the before
  buffer = serialize_int_big_endian(buffer, packet->bytes_rw);
  buffer = serialize_char(buffer, packet->mode);
  buffer = serialize_char_array(buffer, packet->filename);
  buffer = serialize_char_array(buffer, packet->data);

  return buffer; //this is a pointer at the end of buffer
}


inline unsigned char * serialize_request_packet(unsigned char *buffer, struct RequestPacket * packet)
{
  buffer = serialize_char(buffer, packet->mode); //returns a pointer after the end of the before
  buffer = serialize_char_array(buffer, packet->filename);

  return buffer; //this is a pointer at the end of buffer
}

inline unsigned char * serialize_respone_packet(unsigned char *buffer, struct ResponsePacket * packet)
{
  buffer = serialize_char(buffer, packet->status); //returns a pointer after the end of the before

  return buffer; //this is a pointer at the end of buffer
}

inline unsigned char * deserialize_file_packet(unsigned char *buffer, struct FilePacket * packet) {
    //get the first four bytes of the buffer
    
  buffer = deserialize_int_big_endian(buffer, &(packet->offset)); //returns a pointer after the end of the before
  buffer = deserialize_int_big_endian(buffer, &(packet->bytes_rw));
  buffer = deserialize_char(buffer, (char *) &(packet->mode));
  buffer = deserialize_char_array(buffer, packet->filename);
  buffer = deserialize_char_array(buffer, packet->data);

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

inline int get_size_of_request_packet(struct RequestPacket * packet){
    return sizeof(packet->mode) + strlen(packet->filename) + 1; // +1 to accomodate for '\0' character
}


inline int get_size_of_file_packet(struct FilePacket * packet){
    return sizeof(packet->bytes_rw) + sizeof(packet->offset) + sizeof(packet->mode) +
           strlen(packet->data) + 1 + strlen(packet->filename) + 1; // +1 to accomodate for '\0' character
}

inline int write_serialized_data(int fd, unsigned char * buffer, unsigned char * ptr) {           
    return write(fd, buffer, ptr - buffer);   
}

#endif