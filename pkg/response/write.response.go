package response

import "unsafe"

type WriteResponseImpl struct {
	ptr unsafe.Pointer
}

var _ Response = &WriteResponseImpl{}

func (gr *WriteResponseImpl) Free() {
	gr.ptr = nil
}

func (gr *WriteResponseImpl) loadResponse() {
	if gr.ptr == nil {
		return
	}
}

func (gr *WriteResponseImpl) reset() {}
