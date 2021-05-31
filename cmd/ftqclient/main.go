package main

import (
	"fmt"
	"os"

	"github.com/MartinSimango/goftqproto/internal/argloader"
	"github.com/MartinSimango/goftqproto/internal/client"
	"github.com/MartinSimango/goftqproto/pkg/request"
)

func main() {
	loader := argloader.NewArgumentLoaderImpl()
	cmdArgs, err := loader.LoadArgs()

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	factory := request.NewFactoryImpl()

	client := client.NewClientImpl(*cmdArgs, factory)

	if cmdArgs.Server == "" {
		err = client.WriteToSelf()

	} else if !cmdArgs.IsSourceServer {
		err = client.Write()
	} else {
		err = client.Read()
	}

	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	fmt.Println("[Client...] " + "Program Done!!!")

}
