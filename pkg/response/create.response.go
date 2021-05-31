package response

// #cgo LDFLAGS: -lgoresponse
// #include <ftqproto/ResponseWrapper.h>
import "C"
import (
	"unsafe"
)

type CreateResponseImpl struct {
	ptr       unsafe.Pointer
	Filenames []string
	FileSizes []int
	IsDirs    []bool
	NumFiles  int
}

//check that we implement the interface
var _ Response = &CreateResponseImpl{}

//NewCreateResponseImpl is constructor
func NewCreateResponseImpl(C_CreateResponseStructPtr unsafe.Pointer) *CreateResponseImpl {
	cr := CreateResponseImpl{
		ptr: C_CreateResponseStructPtr,
	}
	cr.loadResponse()
	return &cr
}

func (cr *CreateResponseImpl) Free() {
	C.DestroyCreateResponse(cr.ptr)
	cr.ptr = nil
	cr.reset()
}

func (cr *CreateResponseImpl) reset() {
	cr.Filenames = []string{}
	cr.FileSizes = []int{}
	cr.NumFiles = 0
}

func (cr *CreateResponseImpl) loadResponse() {
	if cr.ptr == nil { //memory allocated from C program was deallocated
		return
	}

	response := C.GetCreateResponse(cr.ptr)
	cr.NumFiles = int(response.numFiles)
	start_filenames := unsafe.Pointer(response.filenames)
	start_fileSizes := unsafe.Pointer(response.fileSizes)
	size_filenames := unsafe.Sizeof(_Cgo_ptr) //array of c pointers
	size_fileSizes := unsafe.Sizeof(C.int(0)) // array of c ints
	start_isDirs := unsafe.Pointer(response.isDirs)
	size_isDirs := unsafe.Sizeof(C.char(0)) // array of c ints

	for i := 0; i < cr.NumFiles; i++ {
		response.filenames = (**C.char)(unsafe.Pointer(uintptr(start_filenames) + size_filenames*uintptr(i)))
		response.fileSizes = (*C.int)(unsafe.Pointer(uintptr(start_fileSizes) + size_fileSizes*uintptr(i)))
		response.isDirs = (*C.char)(unsafe.Pointer(uintptr(start_isDirs) + size_isDirs*uintptr(i)))
		cr.Filenames = append(cr.Filenames, C.GoString(*response.filenames))
		cr.FileSizes = append(cr.FileSizes, int(*response.fileSizes))
		if int8(*response.isDirs) > 0 {
			cr.IsDirs = append(cr.IsDirs, true)
		} else {
			cr.IsDirs = append(cr.IsDirs, false)
		}
	}
}
