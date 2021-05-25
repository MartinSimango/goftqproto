package client

import (
	"unsafe"

	cerror "github.com/MartinSimango/gocpperror"
	"github.com/MartinSimango/goftqproto/pkg/response"
)

// #cgo LDFLAGS: -lgocpclient
// #include <ftqproto/ClientWrapper.h>
// #include <cpperror/ErrorCustom.h>
import "C"

const READ = int(C.READ_MODE)
const WRITE = int(C.WRITE_MODE)

type CreateRequestFile struct {
	FilePath string
	FileSize int
}

type FileClient interface {
	Connect(address string, port int) cerror.CPPError
	SendCreateRequest(cr []CreateRequestFile) (*response.CreateResponseImpl, cerror.CPPError)
	SendGetRequest(filepath string) cerror.CPPError
	SendReadRequest(numberOfBytesToRead, offset int, readFile, writeFile string) cerror.CPPError
	SendWriteRequest(numberOfBytesToWrite, offset int, readFile, writeFile string) cerror.CPPError
	Close() cerror.CPPError
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
func (fc FileClientImpl) Connect(address string, port int) cerror.CPPError {
	cerr := cerror.CPPErrorImpl{}
	cerr.Ptr = C.Connect(fc.ptr, C.CString(address), C.int(port))
	errorMessage := cerr.GetErrorMessage()

	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}

func (fc FileClientImpl) SendCreateRequest(cr []CreateRequestFile) (*response.CreateResponseImpl, cerror.CPPError) {

	var CFilenames []*C.char
	var CFileSizes []C.int

	var numFiles int = len(cr)

	cerr := cerror.CPPErrorImpl{}

	for i := 0; i < numFiles; i++ {
		CFilenames = append(CFilenames, C.CString(cr[i].FilePath))
		CFileSizes = append(CFileSizes, C.int(cr[i].FileSize))
	}

	cerr.Ptr = C.SendCreateRequest(fc.ptr, &CFilenames[0], &CFileSizes[0], C.int(numFiles))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return nil, cerr
	}
	var res = response.CreateResponseImpl{}
	res.Ptr = cerr.GetFuncReturnStructValue(uint32(C.CREATE_RESPONSE_STRUCT_TYPE))
	cerr.Free()
	return res.GetResponse(), nil
}

func (fc FileClientImpl) SendGetRequest(filepath string) cerror.CPPError {
	cerr := cerror.CPPErrorImpl{}
	cerr.Ptr = C.SendGetRequest(fc.ptr, C.CString(filepath))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}
func (fc FileClientImpl) SendReadRequest(numberOfBytesToRead, offset int, readFile, writeFile string) cerror.CPPError {
	cerr := cerror.CPPErrorImpl{}
	cerr.Ptr = C.SendReadRequest(fc.ptr, C.int(numberOfBytesToRead), C.int(offset), C.CString(readFile), C.CString(writeFile))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil

}
func (fc FileClientImpl) SendWriteRequest(numberOfBytesToWrite, offset int, readFile, writeFile string) cerror.CPPError {
	cerr := cerror.CPPErrorImpl{}
	cerr.Ptr = C.SendWriteRequest(fc.ptr, C.int(numberOfBytesToWrite), C.int(offset), C.CString(readFile), C.CString(writeFile))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil

}

// Close closes the connection to the server, returns false upon failure
func (fc FileClientImpl) Close() cerror.CPPError {
	cerr := cerror.CPPErrorImpl{}
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
