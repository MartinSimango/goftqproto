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
	start_isDirs := unsafe.Pointer(response.isDirs)

	c_pointer_size := unsafe.Sizeof(_Cgo_ptr)  //array of c pointers
	c_int_size := unsafe.Sizeof(C.int(0))      // array of c ints
	c_bool_size := unsafe.Sizeof(C.bool(true)) // array of c bool

	for i := 0; i < cr.NumFiles; i++ {
		response.filenames = (**C.char)(unsafe.Pointer(uintptr(start_filenames) + c_pointer_size*uintptr(i)))
		response.fileSizes = (*C.int)(unsafe.Pointer(uintptr(start_fileSizes) + c_int_size*uintptr(i)))
		response.isDirs = (*C.bool)(unsafe.Pointer(uintptr(start_isDirs) + c_bool_size*uintptr(i)))
		cr.Filenames = append(cr.Filenames, C.GoString(*response.filenames))
		cr.FileSizes = append(cr.FileSizes, int(*response.fileSizes))
		cr.IsDirs = append(cr.IsDirs, bool(*response.isDirs))
	}
}
