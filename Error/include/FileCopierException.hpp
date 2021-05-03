#pragma once
#include <iostream>
#include <exception>

namespace fce {

    class FileCopierException : public std::exception {
        
        public:
            FileCopierException() : std::exception(){}
            
            virtual char * getErrorMessage(char * error) = 0;
        
    };

    static FileCopierException* AsFileCopierException(void* fce){
        return reinterpret_cast<FileCopierException*>(fce);
    }


    static char* SetErrorMessage(char *errorMessage, void * exception) {
        return AsFileCopierException(exception)->getErrorMessage(errorMessage);
    }

}