package main

import (
	"fmt"
	"os"

	"github.com/MartinSimango/FileCopier/go-client/client"
)

func main() {

	fmt.Println("[Client...] " + "Starting client...")

	fc := client.NewFileClient(client.WRITE, "/home/martin/tlpl.txt", "../Testers/File.txt")
	cerr := fc.Connect("192.168.1.106", 3000, true)
	// fc := client.NewFileClient(client.WRITE, "/Users/martinsimango/tlpl.txt", "../Testers/File.txt")
	// cerr := fc.Connect("127.0.0.1", 3000, true)

	if cerr != nil {
		fmt.Println(cerr.Error())
		os.Exit(1)
	}

	fmt.Println("[Client...] " + "Processing...")

	fileSize, cerr := fc.GetFileSize()

	fmt.Println("FILE size: ", fileSize)

	if cerr != nil {
		fmt.Println(cerr.Error())
		os.Exit(1)
	}

	bytes, cerr := fc.Process(0, fileSize)

	if cerr != nil {
		fmt.Println(cerr.Error())
		os.Exit(1)
	}
	fmt.Println(bytes)

	//cerr := fc.Connect("192.168.1.106", 3000, true)

	if cerr != nil {
		fmt.Println(cerr.Error())
		os.Exit(1)
	}

	fmt.Println("[Client...] " + "Program Done!!!")

}
