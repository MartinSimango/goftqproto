package response

// #cgo CFLAGS: -I../../Response/include
// #cgo LDFLAGS: -L${SRCDIR}/../../Response/lib -lgoreponse
// #include "ResponseWrapper.h"
import "C"
import (
	"unsafe"
)

type CreateResponse interface {
	SetCreateResponse()
	Free()
}
type CreateResponseImpl struct {
	Ptr       unsafe.Pointer
	Filenames []string
	FileSizes []int
	NumFiles  int
}

var _ CreateResponse = &CreateResponseImpl{}

func (cr *CreateResponseImpl) Free() {
	C.DestroyCreateResponse(cr.Ptr)
}

func (cr *CreateResponseImpl) SetCreateResponse() {
	var response = C.GetCreateResponse(cr.Ptr)

	cr.NumFiles = int(response.numFiles)
	start_filenames := unsafe.Pointer(response.filenames)
	start_fileSizes := unsafe.Pointer(response.fileSizes)
	size_filenames := unsafe.Sizeof(_Cgo_ptr) //array of c pointers
	size_fileSizes := unsafe.Sizeof(C.int(0)) // array of c ints

	for i := 0; i < cr.NumFiles; i++ {
		response.filenames = (**C.char)(unsafe.Pointer(uintptr(start_filenames) + size_filenames*uintptr(i)))
		response.fileSizes = (*C.int)(unsafe.Pointer(uintptr(start_fileSizes) + size_fileSizes*uintptr(i)))
		cr.Filenames = append(cr.Filenames, C.GoString(*response.filenames))
		cr.FileSizes = append(cr.FileSizes, int(*response.fileSizes))
	}
}
