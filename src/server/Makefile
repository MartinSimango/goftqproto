CC=gcc
CPP=g++
IDIR=../../include/server ../../include/shared ../../include/file-read-writer ../../include/packet
ODIR=../../obj/client
LDIR=../../lib
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++11


SERVER_SOURCES=$(wildcard *.cpp)
SERVER_OBJECTS=$(patsubst %.cpp, $(ODIR)/%.o, $(SERVER_SOURCES))

SERVER_DEPS = $(patsubst %, %/*, $(IDIR)) 

all: $(SERVER_OBJECTS) build-slib

$(SERVER_OBJECTS): $(ODIR)/%.o : %.cpp $(SERVER_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)


build-slib:
	ar -crs $(LDIR)/libgocpserver.a $(SERVER_OBJECTS)