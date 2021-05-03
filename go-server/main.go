package main

import (
	"fmt"
	"os"

	fileServer "github.com/MartinSimango/FileCopier/go-server/server"
)

func main() {

	fs := fileServer.NewFileServer(3000, "")

	cerr := fs.StartServer(5)

	if cerr != nil {
		fmt.Println(cerr.Error())
		cerr.Free()
		os.Exit(1)
	}

	fmt.Println("[Server...] " + "Server started...")

	accepted, cerr := fs.Accept()

	if cerr != nil {
		fmt.Println(cerr.Error())
		os.Exit(1)
	}

	if !accepted { //TODO throw exception if accepted=false?
		fmt.Println("Could not accept!")
		os.Exit(1)
	}

	fmt.Println("[Server...] " + "Closing server")

	cerr = fs.Close()

	if cerr != nil {
		fmt.Println(cerr.Error())
		os.Exit(1)
	}

	fmt.Println("[Server...] " + "Program succeeded")
}
