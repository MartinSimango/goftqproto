package main

import (
	"fmt"
	"os"

	"github.com/MartinSimango/FileCopier/go-client/client"
)

func main() {

	fmt.Println("Hello World")
	fc := client.NewFileClient(0, "tl.txt", "File.txt")
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
