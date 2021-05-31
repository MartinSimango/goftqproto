package request

import (
	"errors"
	"fmt"
	"os"
	"path/filepath"
)

type Factory interface {
	CreateCreateRequest(filepath, destFilepath string) (*CreateRequest, error)
	CreateGetRequest(filepath string) (*GetRequest, error)
	CreateWriteRequest(filepath string) (*WriteRequest, error)
	CreateReadRequest(filepath string) (*ReadRequest, error)
}

type FactoryImpl struct{}

var _ Factory = &FactoryImpl{}

//NewFactoryImpl is a constructor
func NewFactoryImpl() *FactoryImpl {
	return &FactoryImpl{}
}

func (f *FactoryImpl) CreateCreateRequest(filepath, destFilepath string) (*CreateRequest, error) {
	file, err := os.Stat(filepath)
	if err != nil {
		return nil, err
	}

	if file.IsDir() {
		//traveserse through dir to get all files in folder
		var files []CreateRequestFile

		files = append(files)
		getFiles(filepath)
		return nil, errors.New("TO implement")

	} else {
		requestFile := CreateRequestFile{FilePath: destFilepath, FileSize: int(file.Size()), IsDir: false}
		return &CreateRequest{
			Request: []CreateRequestFile{requestFile},
		}, nil
	}
}

func (f *FactoryImpl) CreateGetRequest(filepath string) (*GetRequest, error) {
	return nil, nil
}
func (f *FactoryImpl) CreateWriteRequest(filepath string) (*WriteRequest, error) {
	return nil, nil
}

func (f *FactoryImpl) CreateReadRequest(filepath string) (*ReadRequest, error) {
	return nil, nil
}

func getFiles(file string) {
	//var files []CreateRequestFile
	err := filepath.Walk(file,
		func(path string, info os.FileInfo, err error) error {
			if err != nil {
				return err
			}
			fmt.Println(path, info.Size())
			// if !info.IsDir() {
			// 	info.Name()
			// }
			return nil
		})
	if err != nil {
		fmt.Println(err)
	}
}
