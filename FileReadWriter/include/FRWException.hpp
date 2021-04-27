#pragma once
#include <iostream>
#include <exception>


static const char * FAILED_TO_RESIZE_FILE = "Failed to resize file.";
static const char * INVALID_FILE_SIZE = "A valid file size needs to be specified when creating a file.";
static const char * FAILED_TO_GET_FILE_SIZE = "Failed to get file size";


static const char * FAILED_TO_OPEN_FILE_FOR_WRITING = "Failed to open file for writing.";
static const char * FAILED_TO_OPEN_FILE_FOR_READING = "Failed to open file for reading.";

static const char * FAILED_TO_CLOSE_FILE = "Failed to close file.";
static const char * FAILED_TO_READ_FROM_FILE = "Failed to read from file.";
static const char * FAILED_TO_WRITE_TO_FILE = "Failed to write to file.";
static const char * FAILED_TO_WRITE_FILE_NOT_OPEN = "Cannot write to unopened file."; 
static const char * FAILED_TO_READ_FILE_NOT_OPEN = "Cannot read to unopened file.";
static const char * FAILED_TO_CLOSE_FILE_NOT_OPEN = "Cannot close unopened file.";


class FRWException : public std::exception {
    
    private:
	    const char* error;
        const char* filename;
    
    public:
        FRWException(const char *error, const char * filename) : std::exception(), error(error), filename(filename){}
    	
        const char * what() const override {
            return error;   
        }

        const char * filename() const {
            return filename;   
        }
       
};
