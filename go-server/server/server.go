package server

import (
	"unsafe"

	"github.com/MartinSimango/FileCopier/go-error/cerror"
)

// #cgo CFLAGS:  -I${SRCDIR}/../../FileServer/include -I../../FilePacket/include -I../../include
// #cgo LDFLAGS: -L${SRCDIR}/../../FileServer/lib -lgocpserver
// #include "ServerWrapper.h"
import "C"

const READ = int(C.READ)
const WRITE = int(C.WRITE)

type FileServer interface {
	StartServer(connections int) cerror.CError
	Accept() (bool, cerror.CError)
	Close() cerror.CError
	GetFileSize() (int, cerror.CError)
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

func (fs *FileServerImpl) StartServer(connections int) cerror.CError {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.StartServer(fs.ptr, C.int(connections))
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil

}

// Accepts waits and accepts a client connection
func (fs *FileServerImpl) Accept() (bool, cerror.CError) {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.Accept(fs.ptr)
	errorMessage := cerr.GetErrorMessage()

	if errorMessage != nil {
		return false, cerr
	}

	retVal := cerr.GetFuncReturnValue().(bool)
	cerr.Free()

	return retVal, nil
}

func (fs *FileServerImpl) GetFileSize() (int, cerror.CError) {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.GetFileServerFileSize(fs.ptr)
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return -1, cerr
	}

	retVal := cerr.GetFuncReturnValue().(int)
	cerr.Free()
	return retVal, nil
}

// Close closes the connection to the server, returns false upon failure
func (fs *FileServerImpl) Close() cerror.CError {
	cerr := cerror.CErrorImpl{}
	cerr.Ptr = C.CloseFileServer(fs.ptr)
	errorMessage := cerr.GetErrorMessage()
	if errorMessage != nil {
		return cerr
	}
	cerr.Free()
	return nil
}
