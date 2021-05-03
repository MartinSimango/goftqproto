#pragma once

#include <type_traits>
#include <ErrorConstants.h>
#include <string.h>
#include <iostream>
#include <Error.hpp>

//TODO partial template decrease code size

template<typename Object, typename... Args>
class Error<void, Object, Args...> : public Delegate<void, Args...>, public ErrorBase {

    protected:

        using MemberFunctionPtrType = typename MemberFunctionPtr<void, Object, Args...>::Type; 
        using FunctionPtrType = typename FunctionPtr<void, Args...>::Type;
        Object * object;
        MemberFunctionPtrType memberFunctionPtr;
        FunctionPtrType* functionPtr;
    
    void setFunctionReturnType(){
        funcReturnType = VOID_TYPE;
    }


    public:

    explicit Error (MemberFunctionPtrType delegateFunc, Object * obj) : ErrorBase(), memberFunctionPtr(delegateFunc), object(obj) {
        setFunctionReturnType(); // used for ErrorWrapper
    }


    ~Error() {
        std::cout << "DESTRUCTIONG Void" <<std::endl;
        delete errorMessage;
        errorMessage = NULL;
    }
   

    virtual void Execute(Args... args) override
    {   
         (object->*memberFunctionPtr)(std::forward<Args>(args)...);
    }
    
};

