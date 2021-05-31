package response

import "unsafe"

type GetResponseImpl struct {
	ptr unsafe.Pointer
}

var _ Response = &GetResponseImpl{}

func (gr *GetResponseImpl) Free() {
	gr.ptr = nil
}

func (gr *GetResponseImpl) loadResponse() {
	if gr.ptr == nil {
		return
	}
}

func (gr *GetResponseImpl) reset() {}
