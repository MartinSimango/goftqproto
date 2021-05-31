package fileclient

import (
	"unsafe"

	cerror "github.com/MartinSimango/gocpperror"
	"github.com/MartinSimango/goftqproto/pkg/request"
	"github.com/MartinSimango/goftqproto/pkg/response"
)

// #cgo LDFLAGS: -lgocpclient
// #include <ftqproto/ClientWrapper.h>
// #include <cpperror/ErrorCustom.h>
import "C"

const READ = int(C.READ_MODE)
const WRITE = int(C.WRITE_MODE)

type FileClient interface {
	Connect(address string, port int) cerror.CPPError
	SendCreateRequest(cr request.CreateRequest) (*response.CreateResponseImpl, cerror.CPPError)
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
func (fc *FileClientImpl) Connect(address string, port int) cerror.CPPError {
	cerr := cerror.NewCPPErrorImpl(C.Connect(fc.ptr, C.CString(address), C.int(port)))
	errorMessage := cerr.GetErrorMessage()

	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}

type Fp struct {
	CFilenames []*C.char
	CFileSizes []C.int
	CIsDirs    []bool
}

func (fc *FileClientImpl) SendCreateRequest(cr request.CreateRequest) (*response.CreateResponseImpl, cerror.CPPError) {

	var CFilenames []*C.char
	var CFileSizes []C.int
	var CIsDirs []C.char

	var numFiles int = len(cr.Request)

	for i := 0; i < numFiles; i++ {
		CFilenames = append(CFilenames, C.CString(cr.Request[i].FilePath))
		CFileSizes = append(CFileSizes, C.int(cr.Request[i].FileSize))
		if cr.Request[i].IsDir {
			CIsDirs = append(CIsDirs, C.char(1))
		} else {
			CIsDirs = append(CIsDirs, C.char(0))

		}

	}

	cerr := cerror.NewCPPErrorImpl(C.SendCreateRequest(fc.ptr, &CFilenames[0], &CFileSizes[0], &CIsDirs[0], C.int(numFiles)))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return nil, cerr
	}
	defer cerr.Free()

	C_CreateResponseStructPtr := cerr.GetFuncReturnStructValue(uint32(C.CREATE_RESPONSE_STRUCT_TYPE))

	return response.NewCreateResponseImpl(C_CreateResponseStructPtr), nil

}

func (fc *FileClientImpl) SendGetRequest(filepath string) cerror.CPPError {
	cerr := cerror.NewCPPErrorImpl(C.SendGetRequest(fc.ptr, C.CString(filepath)))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}
func (fc *FileClientImpl) SendReadRequest(numberOfBytesToRead, offset int, readFile, writeFile string) cerror.CPPError {
	cerr := cerror.NewCPPErrorImpl(C.SendReadRequest(fc.ptr, C.int(numberOfBytesToRead), C.int(offset), C.CString(readFile), C.CString(writeFile)))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil

}
func (fc *FileClientImpl) SendWriteRequest(numberOfBytesToWrite, offset int, readFile, writeFile string) cerror.CPPError {
	cerr := cerror.NewCPPErrorImpl(C.SendWriteRequest(fc.ptr, C.int(numberOfBytesToWrite), C.int(offset), C.CString(readFile), C.CString(writeFile)))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil

}

// Close closes the connection to the server, returns false upon failure
func (fc FileClientImpl) Close() cerror.CPPError {
	cerr := cerror.NewCPPErrorImpl(C.CloseFileClient(fc.ptr))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}

// Free deallocates the memory allocataed to the FileClientImpl instance
func (fc FileClientImpl) Free() {
	fc.Close()
	C.DestroyFileClient(fc.ptr)
}
