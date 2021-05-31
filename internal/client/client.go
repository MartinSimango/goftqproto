package client

import (
	"errors"
	"fmt"

	"github.com/MartinSimango/goftqproto/internal/argloader"
	"github.com/MartinSimango/goftqproto/pkg/fileclient"
	"github.com/MartinSimango/goftqproto/pkg/request"
	"github.com/MartinSimango/goftqproto/pkg/response"
)

type Client interface {
	WriteToSelf() error
	Write() error
	Read() error
	createFiles() (*response.CreateResponseImpl, error)
}

type ClientImpl struct {
	args    argloader.CmdArgs
	factory request.Factory
}

// //check we implement interface
var _ Client = &ClientImpl{}

//ClientImpl is constructor
func NewClientImpl(cmdArgs argloader.CmdArgs, factory request.Factory) *ClientImpl {
	return &ClientImpl{
		args:    cmdArgs,
		factory: factory,
	}
}

func (c *ClientImpl) Write() error {
	response, err := c.createFiles()
	if err != nil {
		return err
	}
	fmt.Println(*response)
	return nil
}

func (c *ClientImpl) createFiles() (*response.CreateResponseImpl, error) {
	//todo start using channels are go functions
	fc := fileclient.NewFileClient()
	defer fc.Free() // free will also close

	cerr := fc.Connect(c.args.Server, c.args.Port)
	if cerr != nil {
		errorMessage := cerr.Error()
		cerr.Free()
		return nil, fmt.Errorf("%s", errorMessage)
	}
	request, err := c.factory.CreateCreateRequest(c.args.SourceFilePath, c.args.DestinationFilePath)
	if err != nil {
		return nil, err
	}

	response, cerr := fc.SendCreateRequest(*request)
	if cerr != nil {
		errorMessage := cerr.Error()
		cerr.Free()
		return nil, fmt.Errorf("%s", errorMessage)
	}
	return response, nil
}

func (c *ClientImpl) Read() error {
	return errors.New("Unimplemented method: Read")
}
func (c *ClientImpl) WriteToSelf() error {
	return errors.New("Unimplemented method: WriteToSelf")

}
