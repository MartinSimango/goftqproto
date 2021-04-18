package server

import "unsafe"

// #cgo CFLAGS:  -I${SRCDIR}/../../FileServer/include -I../../FilePacket/include -I../../include
// #cgo LDFLAGS: -L${SRCDIR}/../../FileServer/lib -lgocpserver
// #include "ServerWrapper.h"
import "C"

const READ = int(C.READ)
const WRITE = int(C.WRITE)

type FileServer interface {
	StartServer(connections int) bool
	Accept() bool
	Close() bool
	GetErrorMessage() string
	Free()
}

type FileServerImpl struct {
	ptr unsafe.Pointer
}

//check the FileServer is implemented
var _ FileServer = &FileServerImpl{}

// NewFileServer creates a new instance of FileServer
func NewFileServer(port int) FileServerImpl {
	var fs = FileServerImpl{}
	fs.ptr = C.NewFileServer(C.int(port))
	return fs
}

// Free deallocates the memory allocataed to the FileClientImpl instance
func (fs *FileServerImpl) Free() {
	C.DestroyFileServer(fs.ptr)
}

func (fs *FileServerImpl) StartServer(connections int) bool {
	return bool(C.StartServer(fs.ptr, C.int(connections)))
}

// Accepts waits and accepts a client connection
func (fs *FileServerImpl) Accept() bool {
	return bool(C.Accept(fs.ptr))
}

// Close closes the connection to the server, returns false upon failure
func (fs *FileServerImpl) Close() bool {
	return bool(C.Close(fs.ptr))
}

// GetErrorMessge returns the errorMessage
func (fs *FileServerImpl) GetErrorMessage() string {
	return C.GoString(C.GetErrorMessage(fs.ptr))
}
