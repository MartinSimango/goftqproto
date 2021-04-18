package client

import (
	"unsafe"
)

// #cgo CFLAGS:  -I${SRCDIR}/../../FileClient/include -I../../FilePacket/include -I../../include
// #cgo LDFLAGS: -L${SRCDIR}/../../FileClient/lib -lgocpclient
// #include "ClientWrapper.h"
import "C"

const READ = int(C.READ)
const WRITE = int(C.WRITE)

type FileClient interface {
	Connect(address string, port int) bool
	Process(offset, numberOfBytesRead int) int
	GetErrorMessage() string
	Close() bool
	Free()
}
type FileClientImpl struct {
	ptr unsafe.Pointer
}

//check the FileClient is implemented
var _ FileClient = &FileClientImpl{}

// NewFileClient creates a new instance of FileClient
func NewFileClient(mode int, requestFile string, filename string) FileClientImpl {
	var fc = FileClientImpl{}
	fc.ptr = C.NewFileClient(C.int(mode), C.CString(requestFile), C.CString(filename))
	return fc
}

// Free deallocates the memory allocataed to the FileClientImpl instance
func (fc FileClientImpl) Free() {
	C.DestroyFileClient(fc.ptr)
}

// Close closes the connection to the server, returns false upon failure
func (fc FileClientImpl) Connect(address string, port int) bool {
	return bool(C.Connect(fc.ptr, C.CString(address), C.int(port)))
}

// Process either reads or writes to the server depending on what mode the FileClient is in
func (fc FileClientImpl) Process(offset, numberOfBytesRead int) int {
	return int(C.Process(fc.ptr, C.int(offset), C.int(numberOfBytesRead)))
}

// Close closes the connection to the server, returns false upon failure
func (fc FileClientImpl) Close() bool {
	return bool(C.Close(fc.ptr))
}

// GetErrorMessge returns the errorMessage
func (fc FileClientImpl) GetErrorMessage() string {
	return C.GoString(C.GetErrorMessage(fc.ptr))
}
