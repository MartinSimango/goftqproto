package response

type Response interface {
	Free()
	reset()
	loadResponse()
}
