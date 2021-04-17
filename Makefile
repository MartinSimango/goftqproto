
SUBDIRS= FileReadWriter FilePacket FileClient FileServer

build-go:
	go build ./...

install: build
	go install ./...

build: $(SUBDIRS) build-go

$(SUBDIRS):
	sudo $(MAKE) -C $@

.PHONY: all $(SUBDIRS)

run: install
	-killall go-server
	-killall go-client
	go-server & go-client

clean:
	sudo $(MAKE) clean -C FileReadWriter
	sudo $(MAKE) clean -C FilePacket
	sudo $(MAKE) clean -C FileClient
	sudo $(MAKE) clean -C FileServer