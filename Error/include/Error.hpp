#pragma once

#include <type_traits>
#include <ErrorConstants.h>
#include <string.h>
#include <iostream>
#include <Delegate.hpp>
#include <ErrorBase.hpp>


template<typename RetVal, typename Object, typename... Args>
class Error: public Delegate<RetVal, Args...>, public ErrorBase {

    protected:

        using MemberFunctionPtrType = typename MemberFunctionPtr<RetVal, Object, Args...>::Type; 
        using FunctionPtrType = typename FunctionPtr<RetVal, Args...>::Type;
        Object * object;
        MemberFunctionPtrType memberFunctionPtr;
        FunctionPtrType* functionPtr;
    
    void setFunctionReturnType(){
        if (std::is_same<RetVal, void>::value) {
            funcReturnType = VOID_TYPE;
        }

        else if (std::is_same<RetVal, int>::value) {
            funcReturnType = INT_TYPE;
        }

        else if (std::is_same<RetVal, bool>::value) {
            funcReturnType = BOOL_TYPE;
        }

        else if (std::is_same<RetVal, char *>::value || std::is_same<RetVal, std::string>::value) {
            funcReturnType = STRING_TYPE;
        }

        else if (std::is_same<RetVal, double>::value) {
            funcReturnType = DOUBLE_TYPE;
        }
        
        else {
            funcReturnType = PTR_TYPE;
        }
    }


    public:

    explicit Error (MemberFunctionPtrType delegateFunc, Object * obj) : ErrorBase(), memberFunctionPtr(delegateFunc), object(obj) {
        setFunctionReturnType(); // used for ErrorWrapper
    }


    ~Error() {
        delete errorMessage;
        delete (RetVal*) retVal;
        errorMessage = NULL;
    }
   

    virtual RetVal Execute(Args... args) override
    {   
         retVal = new RetVal((object->*memberFunctionPtr)(std::forward<Args>(args)...));
         return *reinterpret_cast<RetVal*>(retVal);
    }
    

};

