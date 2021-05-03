package client

import (
	"unsafe"

	"github.com/MartinSimango/FileCopier/go-error/cerror"
)

// #cgo CFLAGS:  -I${SRCDIR}/../../FileClient/include -I../../FilePacket/include -I../../Error/include
// #cgo LDFLAGS: -L${SRCDIR}/../../FileClient/lib -lgocpclient
// #include "ClientWrapper.h"
// #include "ErrorWrapper.h"
import "C"

const READ = int(C.READ)
const WRITE = int(C.WRITE)

type FileClient interface {
	Connect(address string, port int, create bool) cerror.CError
	Process(offset, numberOfBytesRead int) (int, cerror.CError)
	Close() cerror.CError
	GetFileSize() (int, cerror.CError)
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
func (fc FileClientImpl) Connect(address string, port int, create bool) cerror.CError {

	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.Connect(fc.ptr, C.CString(address), C.int(port), C.bool(create))
	errorMessage := cerr.GetErrorMessage()

	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}

// Process either reads or writes to the server depending on what mode the FileClient is in
func (fc FileClientImpl) Process(offset, numberOfBytesRead int) (int, cerror.CError) {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.Process(fc.ptr, C.int(offset), C.int(numberOfBytesRead))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return -1, cerr
	}

	retVal := cerr.GetFuncReturnValue().(int)
	cerr.Free()
	return retVal, nil
}

func (fc FileClientImpl) GetFileSize() (int, cerror.CError) {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.GetFileClientFileSize(fc.ptr)
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return -1, cerr
	}

	retVal := cerr.GetFuncReturnValue().(int)
	cerr.Free()
	return retVal, nil
}

// Close closes the connection to the server, returns false upon failure
func (fc FileClientImpl) Close() cerror.CError {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.CloseFileClient(fc.ptr)
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}
