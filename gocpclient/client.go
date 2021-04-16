package main

import (
	"fmt"
	"os"
	"unsafe"
)

// #cgo CFLAGS:  -I${SRCDIR}/../FileClient/include -I../FilePacket/include -I../include
// #cgo LDFLAGS: -L${SRCDIR}/../FileClient/lib -lgocpclient
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

func main() {

	fmt.Println("Hello World")
	fc := NewFileClient(C.WRITE, "tl.txt", "File.txt")
	if !fc.Connect("localhost", 3000) {
		fmt.Println(fc.GetErrorMessage())
		os.Exit(1)
	}
	if fc.Process(0, 10) < 0 {
		fmt.Println(fc.GetErrorMessage())
		os.Exit(1)
	}
	fmt.Println("Program Done!!!")

}

// bool Connect(void* fc,char * serverAddress, int port);
// // Process either reads or writes to the server depending on what mode the FileClient is in
// // returns the number of bits written or read to the server depending on the mode
// int Process(void* fc,int offset, int numberOfBytesRead);
// // GetErrorMessge returns the errorMessage
// const char * GetErrorMessage(void* fc);
// // Close closes the connection to the server, returns false upon failure
// bool Close(void* fc);
