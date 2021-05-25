package main

import (
	"fmt"
	"os"

	"github.com/MartinSimango/goftqproto/internal/argloader"
	"github.com/MartinSimango/goftqproto/pkg/client"
)

// args
func main() {
	loader := argloader.NewArgumentLoaderImpl()
	cmdArgs, err := loader.LoadArgs()
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println(*cmdArgs)

	fmt.Println("[Client...] " + "Starting client...")

	fc := client.NewFileClient()
	//cerr := fc.Connect("192.168.1.106", 3000)
	// fc := client.NewFileClient(client.WRITE, "/Users/martinsimango/tlpl.txt", "../Testers/File.txt")
	cerr := fc.Connect("127.0.0.1", 3000)

	if cerr != nil {
		fmt.Println(cerr)
		os.Exit(1)
	}

	fi, err := os.Stat("/Users/martinsimango/projects/ftqproto/Testers/File.txt")
	if err != nil {
		os.Exit(1)
	}
	// get the size
	var size int = int(fi.Size())
	fmt.Println("File size is ", size)

	fmt.Println("[Client...] " + "Processing...")

	files := "/Users/martinsimangt"
	fileSize := 30

	fmt.Println(len(("/Users/martinsimango/filecopier/Testers/File_2.txt")))

	response, cerr := fc.SendCreateRequest([]client.CreateRequestFile{{files, fileSize}})

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
