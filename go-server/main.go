package main

import (
	"fmt"
	"os"

	fileServer "github.com/MartinSimango/FileCopier/go-server/server"
)

func main() {

	fs := fileServer.NewFileServer(3000)
	if !fs.StartServer(5) {
		fmt.Println("[Server...] " + fs.GetErrorMessage())
		os.Exit(-1)
	}

	fmt.Println("[Server...] " + "Server started...")

	if !fs.Accept() {
		fmt.Println("[Server...] " + fs.GetErrorMessage())
		os.Exit(-1)
	}
	fmt.Println("[Server...] " + "Closing server")

	if !fs.Close() {
		fmt.Println(fs.GetErrorMessage())
		os.Exit(-1)
	}

	fmt.Println("[Server...] " + "Program succeeded")
}
