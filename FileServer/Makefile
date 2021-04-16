CC=gcc
CPP=g++
IDIR=../../include/server ../../include/shared ../../include/file-read-writer ../../include/packet
ODIR=../../obj/server
LDIR=../../lib
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++11
LIBNAME=libgocpserver

SERVER_SOURCES=$(wildcard *.cpp)
SERVER_OBJECTS=$(patsubst %.cpp, $(ODIR)/%.o, $(SERVER_SOURCES))

SERVER_DEPS = $(patsubst %, %/*, $(IDIR)) 

SERVER_DLIB_SOURCES= $(SERVER_SOURCES) ../file-read-writer/FileReadWriter.cpp ../packet/*.cpp

all: $(SERVER_OBJECTS) build-slib build-dylib

$(SERVER_OBJECTS): $(ODIR)/%.o : %.cpp $(SERVER_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)


build-slib:
	ar -crs $(LDIR)/$(LIBNAME).a $(SERVER_OBJECTS)

build-dylib: $(SERVER_DLIB_SOURCES) $(SERVER_DEPS)
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(SERVER_DLIB_SOURCES) $(CFLAGS)