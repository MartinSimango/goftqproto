#ifndef _SERIALIZE_
#define _SERIALIZE_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define WRITE 0
#define READ 1
#define MEGABYTE 1024*1024

// TODO: reorder struct memebers to decrease file size
struct FilePacket {

    int offset; // where to start writing in the file
    bool messageType; 
    char filename[100]; //file 
    char data[MEGABYTE]; //data to be written

};

//Below functions are from https://stackoverflow.com/questions/1577161/passing-a-structure-through-sockets-in-c


unsigned char * serialize_int_big_endian(unsigned char *buffer, int value)
{
  /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  buffer[0] = value >> 24; // get first byte of int
  buffer[1] = value >> 16; // get second byte of int
  buffer[2] = value >> 8;  // get third byte of int
  buffer[3] = value;    // get fouth byte of int
  return buffer + 4;
}

unsigned char * serialize_int_little_endian(unsigned char *buffer, int value)
{
  /* Write little-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  buffer[0] = value;
  buffer[1] = value >> 8;
  buffer[2] = value >> 16; // get fir byte of int
  buffer[3] = value >> 24; // get second byte of int
  return buffer + 4;
}


unsigned char * serialize_char_array(unsigned char *buffer, char * value)
{
    int value_len = strlen(value)+1; // +1 to include '\0' character too 

    for (int i = 0; i < value_len; i++){
    
        buffer[i] = value[i];
        printf("Read: %c written: %c len: %i \n", buffer[i], value[i], value_len);
    }
    return buffer + value_len;
}


unsigned char * serialize_char(unsigned char *buffer, char value)
{
    buffer[0] = value;
    return buffer + 1;
}


unsigned char * deserialize_int_big_endian(unsigned char *buffer, int *value)
{   
    for (int i = 0; i < 4; i++) {
       *value += pow(2, 3-i) * buffer[i];
    }
    return buffer + 4;

}
unsigned char * deserialize_int_little_endian(unsigned char *buffer, int *value){

    for (int i = 0; i < 4; i++) {
       *value += pow(2, i) * buffer[i];
    }
    return buffer + 4;
    
}

unsigned char * deserialize_char_array(unsigned char *buffer, char * value)
{
    int i = 0;

    while(buffer[i] != '\0'){
        value[i] = buffer[i];
        i++;
    }

    return buffer + (i + 1);
}


unsigned char * deserialize_char(unsigned char *buffer, char* value)
{
    *value = buffer[0];
    return buffer + 1;
}


unsigned char * serialize_file_packet(unsigned char *buffer, struct FilePacket * packet)
{
  buffer = serialize_int_big_endian(buffer, packet->offset); //returns a pointer after the end of the before
  buffer = serialize_char(buffer, packet->messageType);
  buffer = serialize_char_array(buffer, packet->filename);
  buffer = serialize_char_array(buffer, packet->data);


  return buffer; //this is a pointer at the end of buffer
}


unsigned char * deserialize_file_packet(unsigned char *buffer, struct FilePacket * packet) {
    //get the first four bytes of the buffer
    
  buffer = deserialize_int_big_endian(buffer, &(packet->offset)); //returns a pointer after the end of the before
  buffer = deserialize_char(buffer, (char *) &(packet->messageType));
  buffer = deserialize_char_array(buffer, packet->filename);
  buffer = deserialize_char_array(buffer, packet->data);

  return buffer;

}


#endif