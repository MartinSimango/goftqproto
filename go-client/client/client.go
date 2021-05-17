package client

import (
	"unsafe"

	"github.com/MartinSimango/FileCopier/go-utils/cerror"
	"github.com/MartinSimango/FileCopier/go-utils/response"
)

// #cgo CFLAGS:  -I${SRCDIR}/../../FileClient/include -I../../Error/include
// #cgo LDFLAGS: -L${SRCDIR}/../../FileClient/lib -lgocpclient
// #include "ClientWrapper.h"
// #include "ErrorWrapper.h"
import "C"

const READ = int(C.READ_MODE)
const WRITE = int(C.WRITE_MODE)

type FileClient interface {
	Connect(address string, port int) cerror.CError
	SendCreateRequest(filenames []string, fileSizes []int) (*response.CreateResponseImpl, cerror.CError)
	SendGetRequest(filepath string) cerror.CError
	SendReadRequest(numberOfBytesToRead, offset int, readFile, writeFile string) cerror.CError
	SendWriteRequest(numberOfBytesToWrite, offset int, readFile, writeFile string) cerror.CError
	Close() cerror.CError
	Free()
}

type FileClientImpl struct {
	ptr unsafe.Pointer
}

//check the FileClient is implemented
var _ FileClient = &FileClientImpl{}

// NewFileClient creates a new instance of FileClient
func NewFileClient() FileClientImpl {
	var fc = FileClientImpl{}
	fc.ptr = C.NewFileClient()
	return fc
}

// Close closes the connection to the server, returns false upon failure
func (fc FileClientImpl) Connect(address string, port int) cerror.CError {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.Connect(fc.ptr, C.CString(address), C.int(port))
	errorMessage := cerr.GetErrorMessage()

	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}
func (fc FileClientImpl) SendCreateRequest(filenames []string, fileSizes []int) (*response.CreateResponseImpl, cerror.CError) {

	var CFilenames []*C.char
	var CFileSizes []C.int
	var numFiles int = len(filenames)

	cerr := cerror.CErrorImpl{}
	for i := 0; i < numFiles; i++ {
		CFilenames = append(CFilenames, C.CString(filenames[i]))
		CFileSizes = append(CFileSizes, C.int(fileSizes[i]))
	}

	cerr.Ptr = C.SendCreateRequest(fc.ptr, &CFilenames[0], &CFileSizes[0], C.int(numFiles))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return nil, cerr
	}
	var cr = response.CreateResponseImpl{}
	cr.Ptr = cerr.GetFuncReturnValue().(unsafe.Pointer)

	cr.SetCreateResponse()
	cerr.Free()
	return &cr, nil
}

func (fc FileClientImpl) SendGetRequest(filepath string) cerror.CError {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.SendGetRequest(fc.ptr, C.CString(filepath))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}
func (fc FileClientImpl) SendReadRequest(numberOfBytesToRead, offset int, readFile, writeFile string) cerror.CError {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.SendReadRequest(fc.ptr, C.int(numberOfBytesToRead), C.int(offset), C.CString(readFile), C.CString(writeFile))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil

}
func (fc FileClientImpl) SendWriteRequest(numberOfBytesToWrite, offset int, readFile, writeFile string) cerror.CError {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.SendWriteRequest(fc.ptr, C.int(numberOfBytesToWrite), C.int(offset), C.CString(readFile), C.CString(writeFile))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil

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

// Free deallocates the memory allocataed to the FileClientImpl instance
func (fc FileClientImpl) Free() {
	C.DestroyFileClient(fc.ptr)
}
