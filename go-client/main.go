package main

import (
	"fmt"
	"os"

	"github.com/MartinSimango/FileCopier/go-client/client"
)

func main() {

	fmt.Println("[Client...] " + "Starting client...")

	fc := client.NewFileClient()
	//cerr := fc.Connect("192.168.1.106", 3000)
	// fc := client.NewFileClient(client.WRITE, "/Users/martinsimango/tlpl.txt", "../Testers/File.txt")
	cerr := fc.Connect("127.0.0.1", 3000)

	if cerr != nil {
		fmt.Println(cerr.Error())
		os.Exit(1)
	}
	fi, err := os.Stat("/Users/martinsimango/filecopier/Testers/File.txt")
	if err != nil {
		os.Exit(1)
	}
	// get the size
	var size int = int(fi.Size())
	fmt.Println("File size is ", size)

	fmt.Println("[Client...] " + "Processing...")

	files := []string{"/Users/martinsimango/filecopier/Testers/File_2.txt", "a"}
	fileSize := []int{30, 20}

	fmt.Println(len(("/Users/martinsimango/filecopier/Testers/File_2.txt")))

	response, cerr := fc.SendCreateRequest(files, fileSize)

	if cerr != nil {
		fmt.Println(cerr.Error())
		os.Exit(1)
	}

	fmt.Println("Recieved from server: ....")
	fmt.Println(response.Filenames)
	fmt.Println(response.FileSizes)
	fmt.Println(response.NumFiles)

	response.Free()

	fmt.Println("[Client...] " + "Program Done!!!")

}
