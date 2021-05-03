#pragma once
#include <stdio.h>

class ErrorBase {
    protected:
    char *errorMessage;
    int funcReturnType;
    void * retVal;

    public:

    ErrorBase(){
       // retVal = NULL;
        errorMessage = NULL;
        funcReturnType = -1;
    }

    virtual ~ErrorBase(){ }

    virtual char * getErrorMessage() const {
        return errorMessage;
    }
   
    template<typename RetVal> RetVal* getFunctionReturnValue(){
        return reinterpret_cast<RetVal *>(retVal);
    }

    virtual int getFunctionReturnType() {
        return funcReturnType;
    }

    virtual void SetErrorMessage(typename FunctionPtr<char *, char * >::Type functionPtr) {
        errorMessage = new char[ERROR_MAX_LENGTH];
        functionPtr(errorMessage);
    }

    template<typename T>
    void SetErrorMessage(typename MemberFunctionPtr<char*, T, char *>::Type memberFunctionPtr, T* obj) {
        errorMessage = new char[ERROR_MAX_LENGTH];
        errorMessage = (obj->*memberFunctionPtr)(errorMessage);
    }
};
