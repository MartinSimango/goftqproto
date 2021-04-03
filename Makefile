# build:
# 	go build ./...
# 	# add instructions for compiling C files
# install: build
# 	go install ./...
# run: server /
# 	 client

build: server client

run: 
	./server && ./client

server: FileReadWriter.hpp serialize.h simple-server/Server.hpp 
	g++ -o server simple-server/Server.cpp

client: FileReadWriter.hpp simple-client/Client.hpp serialize.h 
	g++ -o client simple-client/Client.cpp