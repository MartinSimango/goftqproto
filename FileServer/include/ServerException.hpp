#pragma once
#include <FileCopierException.hpp>

static const char * FAILED_TO_BIND_SERVER_SOCKET = "Failed to bind the server socket.";
static const char * FAILED_TO_CREATE_SERVER_SOCKET = "Failed to create the server socket!";
static const char * SERVER_FAILED_TO_START_LISTENING = "Server failed to start listening!";
static const char * SERVER_NOT_RUNNING = "The server is not running!";
static const char * FAILED_TO_CLOSE_SERVER_SOCKET = "Failed to close the server socket.";


class ServerException : public fce::FileCopierException {
    
    private:
	    const char* error;
    
    public:
        ServerException(const char *error) : fce::FileCopierException(), error(error){}
    	
        const char * what() const throw() override {
            return error;   
        }

        char * getErrorMessage(char * error) override {
            sprintf(error, "[ServerException] Error: %s", this->error);
            return error;
        }
};
