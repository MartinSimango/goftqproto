#pragma once
#ifdef __cplusplus
extern "C" {
#endif

inline unsigned char * serialize_int_big_endian(unsigned char *buffer, int value);

inline unsigned char * serialize_int_little_endian(unsigned char *buffer, int value);

inline unsigned char * serialize_char_array(unsigned char *buffer, char * value);

inline unsigned char * serialize_char(unsigned char *buffer, char value);

inline unsigned char * deserialize_int_big_endian(unsigned char *buffer, int *value);

inline unsigned char * deserialize_int_little_endian(unsigned char *buffer, int *value);

inline unsigned char * deserialize_char_array(unsigned char *buffer, char * value);

inline unsigned char * deserialize_char(unsigned char *buffer, char* value);

#ifdef __cplusplus
}  // extern "C"
#endif
