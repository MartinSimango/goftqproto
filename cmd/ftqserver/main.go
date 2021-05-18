package main

import (
	"fmt"
	"os"

	"github.com/MartinSimango/FileCopier/pkg/server"
)

func main() {

	rootFolder := os.Getenv("ROOT_FOLDER")
	fs := server.NewFileServer(3000, rootFolder)

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
		os.Exit(1)
	}
	fmt.Println("Handling requests")

	requestOk := true
	for requestOk {
		requestOk, cerr = fs.HandleClientRequest()

		if cerr != nil {
			fmt.Println(cerr.Error())
			break
		}
	}

	fmt.Println("[Server...] " + "Closing server")

	cerr = fs.Close()

	if cerr != nil {
		fmt.Println(cerr.Error())
		os.Exit(1)
	}

	fmt.Println("[Server...] " + "Server closed")
}
