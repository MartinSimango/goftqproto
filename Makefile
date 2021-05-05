
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
docker-build-arm:
	docker build -t martinsimango/filecopierbase:ARM_latest.
	docker build -f go-server/Dockerfile -t martinsimango/gocpserver:ARM_latest.

docker-build-x86_64:
	docker build -t martinsimango/filecopierbase:x86_64_latest .
	docker build -f go-server/Docker_x86_64/Dockerfile -t martinsimango/gocpserver:x86_64_latest .

docker-push-arm:
	docker push martinsimango/filecopierbase:ARM_latest
	docker push martinsimango/gocpserver:ARM_latest

docker-push-x86_64:
	docker push martinsimango/filecopierbase:x86_64_latest
	docker push martinsimango/gocpserver:x86_64_latest

docker-run-server:
	docker run -p 3000:3000 -it -v /:/host/ --env-file .env --name=gocpserver martinsimango/gocpserver

clean:
	$(MAKE) clean -C FileReadWriter
	$(MAKE) clean -C FilePacket
	$(MAKE) clean -C FileClient
	$(MAKE) clean -C FileServer
	$(MAKE) clean -C Error