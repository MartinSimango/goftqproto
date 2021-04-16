#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// Below functions are based from https://stackoverflow.com/questions/1577161/passing-a-structure-through-sockets-in-c

inline unsigned char * serialize_int_big_endian(unsigned char *buffer, int value)
{
  /* Write big-endian int value into buffer; assumes 32-bit int and 8-bit char. */
  buffer[0] = value >> 24; // get first byte of int
  buffer[1] = value >> 16; // get second byte of int
  buffer[2] = value >> 8;  // get third byte of int
  buffer[3] = value;    //get fouth byte of int
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
    value[i] = '\0';
    return buffer + (i + 1);
}


inline unsigned char * deserialize_char(unsigned char *buffer, char* value)
{
    *value = buffer[0];
    return buffer + 1;
}

