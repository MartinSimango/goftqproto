package request

type CreateRequestFile struct {
	FilePath string
	FileSize int
	IsDir    bool
}

type CreateRequest struct {
	Request []CreateRequestFile
}
