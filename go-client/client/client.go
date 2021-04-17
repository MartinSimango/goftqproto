package client

import "unsafe"

// #cgo CFLAGS:  -I${SRCDIR}/../../FileClient/include -I../../FilePacket/include -I../../include
// #cgo LDFLAGS: -L${SRCDIR}/../../FileClient/lib -lgocpclient
// #include "ClientWrapper.h"
import "C"

type FileClient interface {
	Connect(address string, port C.int) C.bool
	Process(offset, numberOfBytesRead C.int) C.int
	GetErrorMessage() string
	Close() C.bool
	Free()
}
type FileClientImpl struct {
	ptr unsafe.Pointer
}

var _ FileClient = &FileClientImpl{}

func NewFileClient(mode C.int, requestFile string, filename string) FileClient {
	var fc = FileClientImpl{}
	fc.ptr = C.NewFileClient(mode, C.CString(requestFile), C.CString(filename))
	return fc
}

func (fc FileClientImpl) Free() {
	C.DestroyFileClient(fc.ptr)

}

func (fc FileClientImpl) Connect(address string, port C.int) C.bool {
	return C.Connect(fc.ptr, C.CString("127.0.0.1"), port)
}

func (fc FileClientImpl) Process(offset, numberOfBytesRead C.int) C.int {
	return C.Process(fc.ptr, offset, numberOfBytesRead)
}

func (fc FileClientImpl) Close() C.bool {
	return C.Close(fc.ptr)
}

func (fc FileClientImpl) GetErrorMessage() string {
	return C.GoString(C.GetErrorMessage(fc.ptr))
}
