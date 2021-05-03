
# SUBDIRS= FileReadWriter FilePacket FileClient FileServer

build: build-c build-go

build-c:
	$(MAKE) -C FileReadWriter
	$(MAKE) -C FilePacket
	$(MAKE) -C FileClient
	$(MAKE) -C FileServer
	$(MAKE) -C Error

build-go:
	go build ./...

install: build 
	go install ./...

install-go: 
	go build ./...
	go install ./...



# $(SUBDIRS):
# 	$(MAKE) -C $@

run: install
	-killall go-server
	-killall go-client
	go-server & go-client

# --- Docker related ---
docker-build:
	docker build -t martinsimango/filecopierbase:latest .
	docker build -f go-server/Dockerfile  -t martinsimango/gocpserver:latest .

docker-push:
    docker push martinsimango/filecopierbase:latest
	docker push martinsimango/gocpserver:latest

docker-run-server:
	docker run -p 3000:3000 -it -v /:/host/ --env-file .env --name=gocpserver martinsimango/gocpserver:latest

clean:
	$(MAKE) clean -C FileReadWriter
	$(MAKE) clean -C FilePacket
	$(MAKE) clean -C FileClient
	$(MAKE) clean -C FileServer
	$(MAKE) clean -C Error