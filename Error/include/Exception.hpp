#pragma once
#include <iostream>
#include <exception>

namespace exep {

    class Exception : public std::exception {
        
        public:
            Exception() : std::exception(){}
            
            virtual char * getErrorMessage(char * error) = 0;
        
    };

}