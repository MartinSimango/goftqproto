SUBDIRS=Error FileClient FileReadWriter FileServer Request Response
SUBDIRS_CLEAN=$(patsubst %, %.clean, $(SUBDIRS))

.PHONY: $(SUBDIRS) $(SUBDIRS_CLEAN) clean

$(SUBDIRS): 
	$(MAKE) -C $(patsubst %,%, $@)

$(SUBDIRS_CLEAN):
	$(MAKE) clean -C $(patsubst %.clean,%, $@)

build: build-c build-go

build-c: $(SUBDIRS)

build-go:
	go build ./...

install: build 
	go install ./...

install-go: 
	go build ./...
	go install ./...




# $(CLIENT_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.cpp $(CLIENT_DEPS)
# 	$(CPP) -c $< -o $@ $(CFLAGS)
run: install
	-killall go-server
	-killall go-client
	go-server & go-client

# --- Docker related ---
docker-build-arm:
	docker build -t martinsimango/filecopierbase:ARM_latest.
	docker build -f go-server/Dockerfile_ARM -t martinsimango/gocpserver:ARM_latest.

docker-build-x86_64:
	docker build -t martinsimango/filecopierbase:x86_64_latest .
	docker build -f go-server/Dockerfile_x86_64 -t martinsimango/gocpserver:x86_64_latest .

docker-push-arm:
	docker push martinsimango/filecopierbase:ARM_latest
	docker push martinsimango/gocpserver:ARM_latest

docker-push-x86_64:
	docker push martinsimango/filecopierbase:x86_64_latest
	docker push martinsimango/gocpserver:x86_64_latest

docker-run-server:
	docker run -p 3000:3000 -it -v /:/host/ --env-file .env --name=gocpserver martinsimango/gocpserver

clean: $(SUBDIRS_CLEAN)

