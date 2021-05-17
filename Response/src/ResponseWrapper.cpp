#include <ResponseWrapper.h>
#include <CreateResponse.hpp>

CreateResponseStruct* AsCreateResponse(void* cr) { 
    return reinterpret_cast<CreateResponseStruct*>(cr); 
}

void DestroyCreateResponse(void *cr) {
    CreateResponseStruct *crs = AsCreateResponse(cr);
    for(int i = 0 ;i < crs->numFiles; i++){
        delete crs->filenames[i];
    }
    delete [] crs->filenames;
    delete [] crs->fileSizes;

}

CreateResponseStruct GetCreateResponse(void *cr) {
    return *AsCreateResponse(cr);
}
