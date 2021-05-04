#pragma once
#include <Exception.hpp>


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


class FRWException : public exep::Exception {
    
    private:
	    const char* error;
        const char* filename;
    
    public:
        FRWException(const char *error, const char * filename) : exep::Exception(), error(error), filename(filename){}
    	
        const char * what() const throw() override {
            return error;   
        }

        const char * getFilename() const {
            return filename;   
        }
        
        char * getErrorMessage(char * error) override {
            sprintf(error, "[FRWException] Error: %s\n[FRWException] File: %s\n", this->error, this->filename);
            return error;
        }
       
};
