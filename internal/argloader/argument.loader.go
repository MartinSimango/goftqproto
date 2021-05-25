package argloader

import (
	"errors"
	"flag"
	"fmt"
	"strings"
)

type ArgumentLoader interface {
	init()
	LoadArgs() (*CmdArgs, error)
}

type ArgumentLoaderImpl struct {
	usageSet bool
	usage    string
}

//check we implement interface
var _ ArgumentLoader = &ArgumentLoaderImpl{}

//NewArgumentLoaderImpl is construct
func NewArgumentLoaderImpl() *ArgumentLoaderImpl {
	var loader ArgumentLoaderImpl
	loader.init()
	return &loader
}

func (al *ArgumentLoaderImpl) init() {
	al.usageSet = true
	al.usage = `usage: ftqclient [-P port]
	source ... target`

	flag.Usage = func() {
		fmt.Println(al.usage)
	}
}

//LoadArgs loads the arguments and flags from the command line into the return CmdArgs struct
func (al *ArgumentLoaderImpl) LoadArgs() (*CmdArgs, error) {

	if !al.usageSet {
		return nil, errors.New("Usage not set")
	}
	// Get flags
	port := flag.Int("P", 3000, "Port") // todo read server port from C file
	flag.Parse()

	//Get args
	args := flag.Args()

	if len(args) < 2 {
		return nil, errors.New(al.usage)
	}

	source, destination := args[0], args[1]
	server := getServer(&source, &destination)
	return &CmdArgs{
		Port:                *port,
		SourceFilePath:      source,
		DestinationFilePath: destination,
		Server:              server,
	}, nil
}

func getServer(source, destination *string) string {

	server := "127.0.0.1"

	sourceColonIdx := strings.Index(*source, ":")
	isSourceServer := sourceColonIdx > 0

	destinationColonIdx := strings.Index(*destination, ":")
	isDestinationServer := destinationColonIdx > 0

	if isSourceServer {
		server = (*source)[:sourceColonIdx]
		*source = (*source)[sourceColonIdx+1:]

	} else if isDestinationServer {

		server = (*destination)[:destinationColonIdx]
		*destination = (*destination)[destinationColonIdx+1:]
	}

	return server
}
