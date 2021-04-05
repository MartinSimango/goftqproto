#ifndef _ERROR_
#define _ERROR_

// SOCKET ERRORS
const char * FAILED_TO_CREATE_SOCKET = "Failed to create the socket!";
const char * FAILED_TO_CONNECT_TO_SERVER = "Failed to connect to the server!";
const char * FAILED_TO_ACCECT_CLIENT = "Failed to accept client connecion!";
const char * FAILED_TO_CLOSE_SOCKET = "Failed to close the socket!";
const char * CLIENT_ALREADY_CONNECTED = "The client is already connected to a server";
const char * CLIENT_NOT_CONNECTED = "The client is not connted to the server";
const char * FAILED_TO_READ_FROM_SERVER_SOCKET = "Failed to read from server socket!";
const char * FAILED_TO_WRITE_TO_SERVER_SOCKET = "Failed to write to server socket!";
const char * FAILED_TO_READ_FROM_CLIENT_SOCKET = "Failed to read from client socket!";
const char * FAILED_TO_WRITE_TO_CLIENT_SOCKET = "Failed to write to client socket!";


//FILE ERRORS
const char * FAILED_TO_OPEN_FILE = "Failed to open file!";
const char * FAILED_TO_CLOSE_FILE = "Failed to close file!";
const char * FAILED_TO_READ_FROM_FILE = "Failed to read from file!";
const char * FAILED_TO_WRITE_TO_FILE = "Failed to write to file!";

//SERVER ERRORS
const char * SERVER_NOT_RUNNING = "The server is not running!";
const char * FAILED_TO_READ_CLIENT_REQUEST= "Failed to read client request!";


#endif