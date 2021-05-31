package response

import "unsafe"

type ReadResponseImpl struct {
	ptr unsafe.Pointer
}

var _ Response = &ReadResponseImpl{}

func (rr *ReadResponseImpl) Free() {
	rr.ptr = nil
}

func (rr *ReadResponseImpl) loadResponse() {
	if rr.ptr == nil {
		return
	}
}

func (rr *ReadResponseImpl) reset() {}
