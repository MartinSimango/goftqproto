CC=gcc
CPP=g++
IDIR=../../include/client ../../include/shared ../../include/file-read-writer ../../include/packet
ODIR=../../obj/client
LDIR=../../lib
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++11


CLIENT_SOURCES=$(wildcard *.cpp)
CLIENT_OBJECTS=$(patsubst %.cpp, $(ODIR)/%.o, $(CLIENT_SOURCES))

CLIENT_DEPS = $(patsubst %, %/*, $(IDIR)) 

all: $(CLIENT_OBJECTS) build-slib

$(CLIENT_OBJECTS): $(ODIR)/%.o : %.cpp $(CLIENT_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)


build-slib:
	ar -crs $(LDIR)/libgocpclient.a $(CLIENT_OBJECTS)