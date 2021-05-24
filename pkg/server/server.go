package server

import (
	"unsafe"

	cerror "github.com/MartinSimango/gocpperror"
)

// #cgo LDFLAGS: -lgocpserver
// #include <ServerWrapper.h>
import "C"

const READ = int(C.READ_MODE)
const WRITE = int(C.WRITE_MODE)

type FileServer interface {
	StartServer(connections int) cerror.CPPError
	Accept() cerror.CPPError
	Close() cerror.CPPError
	HandleClientRequest() (bool, cerror.CPPError)
	IsServerRunning() (bool, cerror.CPPError)
	Free()
}

type FileServerImpl struct {
	ptr unsafe.Pointer
}

//check the FileServer is implemented
var _ FileServer = &FileServerImpl{}

// NewFileServer creates a new instance of FileServer
func NewFileServer(port int, rootFolder string) FileServerImpl {
	var fs = FileServerImpl{}
	fs.ptr = C.NewFileServer(C.int(port), C.CString(rootFolder))
	return fs
}

// Free deallocates the memory allocataed to the FileClientImpl instance
func (fs *FileServerImpl) Free() {
	C.DestroyFileServer(fs.ptr)
}

func (fs *FileServerImpl) StartServer(connections int) cerror.CPPError {
	cerr := cerror.CPPErrorImpl{}
	cerr.Ptr = C.StartServer(fs.ptr, C.int(connections))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil

}

// Accepts waits and accepts a client connection
func (fs *FileServerImpl) Accept() cerror.CPPError {
	cerr := cerror.CPPErrorImpl{}
	cerr.Ptr = C.Accept(fs.ptr)
	errorMessage := cerr.GetErrorMessage()

	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}

// TODO ftq will now return a request and this will be name name GetClientRequest
func (fs *FileServerImpl) HandleClientRequest() (bool, cerror.CPPError) {
	cerr := cerror.CPPErrorImpl{}
	cerr.Ptr = C.HandleClientRequest(fs.ptr)
	errorMessage := cerr.GetErrorMessage()

	if errorMessage != nil {
		return false, cerr
	}
	retVal := cerr.GetFuncReturnValue().(bool)
	cerr.Free()
	return retVal, nil
}

func (fs *FileServerImpl) IsServerRunning() (bool, cerror.CPPError) {
	cerr := cerror.CPPErrorImpl{}
	cerr.Ptr = C.IsServerRunning(fs.ptr)
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return false, cerr
	}
	retVal := cerr.GetFuncReturnValue().(bool)
	cerr.Free()
	return retVal, nil
}

// Close closes the connection to the server, returns false upon failure
func (fs *FileServerImpl) Close() cerror.CPPError {
	cerr := cerror.CPPErrorImpl{}
	cerr.Ptr = C.CloseFileServer(fs.ptr)
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}
