#pragma once
#include <iostream>
#include <exception>

namespace fce {

    class FileCopierException : public std::exception {
        
        public:
            FileCopierException() : std::exception(){}
            
            virtual char * getErrorMessage(char * error) = 0;
        
    };

}