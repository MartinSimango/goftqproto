# build:
# 	go build ./...
# 	# add instructions for compiling C files
# install: build
# 	go install ./...
# run: server /
# 	 client

build: server client

build-no-warning: server-nw client-nw

run: 
	./server && ./client

server: simple-server/* Packet/* simple-file-read-writer/* serialize.h error.h
	g++ -o server simple-server/Server.cpp simple-file-read-writer/FileReadWriter.cpp

client: simple-client/* Packet/* simple-file-read-writer/* serialize.h 
	g++ -o client simple-client/Client.cpp

server-nw: simple-server/* Packet/* simple-file-read-writer/* serialize.h error.h
	g++ -o server simple-server/Server.cpp simple-file-read-writer/FileReadWriter.cpp simple-server/server_test.cpp -w


client-nw: simple-client/* Packet/* simple-file-read-writer/* serialize.h 
		g++ -o client simple-client/Client.cpp simple-file-read-writer/FileReadWriter.cpp simple-client/client_test.cpp -w

