package main

import (
	"fmt"
	"os"

	fileServer "github.com/MartinSimango/FileCopier/go-server/server"
)

func main() {

	fs := fileServer.NewFileServer(3000, "")

	fs.StartServer(5)

	fmt.Println("[Server...] " + "Server started...")

	if !fs.Accept() {
		fmt.Println("[Server...] " + fs.GetErrorMessage())
		os.Exit(-1)
	}
	fmt.Println("[Server...] " + "Closing server")

	fs.Close()

	fmt.Println("[Server...] " + "Program succeeded")
}
