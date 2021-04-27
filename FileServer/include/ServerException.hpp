#pragma once
#include <iostream>
#include <exception>

// SOCKET ERRORS
// static const char * FAILED_TO_CREATE_SOCKET = "Failed to create the socket!";
// static const char * FAILED_TO_CONNECT_TO_SERVER = "Failed to connect to the server!";
// static const char * FAILED_TO_ACCECT_CLIENT = "Failed to accept client connecion!";
// static const char * FAILED_TO_CLOSE_SOCKET = "Failed to close the socket!";
// static const char * CLIENT_ALREADY_CONNECTED = "The client is already connected to a server";
// static const char * CLIENT_NOT_CONNECTED = "The client is not connted to the server";
// static const char * FAILED_TO_READ_FROM_SERVER_SOCKET = "Failed to read from server socket!";
// static const char * FAILED_TO_WRITE_TO_SERVER_SOCKET = "Failed to write to server socket!";
// static const char * FAILED_TO_READ_FROM_CLIENT_SOCKET = "Failed to read from client socket!";
// static const char * FAILED_TO_WRITE_TO_CLIENT_SOCKET = "Failed to write to client socket!";

static const char * FAILED_TO_BIND_SERVER_SOCKET = "Failed to bind the server socket.";
static const char * FAILED_TO_CREATE_SERVER_SOCKET = "Failed to create the server socket!";
static const char * SERVER_FAILED_TO_START_LISTENING = "Server failed to start listening!";
static const char * SERVER_NOT_RUNNING = "The server is not running!";



class ServerException : public std::exception {
    
    private:
	    const char* error;
    
    public:
        ServerException(const char *error) : std::exception(), error(error){}
    	
        const char * what() const override {
            return error;   
        }
       
};
