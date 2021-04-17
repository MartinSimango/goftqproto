package main

import (
	"fmt"
	"os"

	"github.com/MartinSimango/FileCopier/go-client/client"
)

func main() {

	fc := client.NewFileClient(client.WRITE, "tl.txt", "../File.txt")
	if !fc.Connect("127.0.0.1", 3000) {
		fmt.Println("[Client...] " + fc.GetErrorMessage())
		os.Exit(1)
	}
	fmt.Println("[Client...] " + "Processing...")
	if fc.Process(0, 10) < 0 {
		fmt.Println("[Client...] " + fc.GetErrorMessage())
		os.Exit(1)
	}
	fmt.Println("[Client...] " + "Program Done!!!")

}
