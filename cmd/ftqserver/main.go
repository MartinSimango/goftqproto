package main

import (
	"fmt"
	"os"

	"github.com/MartinSimango/goftqproto/pkg/fileserver"
)

func main() {

	rootFolder := os.Getenv("ROOT_FOLDER")
	fs := fileserver.NewFileServer(3000, rootFolder)

	cerr := fs.StartServer(5)

	if cerr != nil {
		fmt.Println(cerr.Error())
		cerr.Free()
		os.Exit(1)
	}

	fmt.Println("[Server...] " + "Server started...")

	cerr = fs.Accept()

	if cerr != nil {
		fmt.Println(cerr.Error())
		cerr.Free()
		os.Exit(1)
	}
	fmt.Println("Handling requests")

	requestOk := true
	for requestOk {
		requestOk, cerr = fs.HandleClientRequest() // todo seperate into getting request and handling it

		if cerr != nil {
			fmt.Println(cerr.Error())
			cerr.Free()
			break
		}
	}

	fmt.Println("[Server...] " + "Closing server")

	cerr = fs.Close()

	if cerr != nil {
		fmt.Println(cerr.Error())
		cerr.Free()
		os.Exit(1)
	}

	fmt.Println("[Server...] " + "Server closed")
}
