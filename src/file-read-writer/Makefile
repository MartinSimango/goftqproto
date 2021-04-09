CC=gcc
CPP=g++
IDIR=../../include/file-read-writer ../../include/packet
ODIR=../../obj/file-read-writer
LDIR=../../lib
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++11


FRW_SOURCES=$(wildcard *.cpp)
FRW_OBJECTS=$(patsubst %.cpp, $(ODIR)/%.o, $(FRW_SOURCES))

FRW_DEPS = $(patsubst %, %/*, $(IDIR)) 

all: $(FRW_OBJECTS) build-slib

$(FRW_OBJECTS): $(ODIR)/%.o : %.cpp $(FRW_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)


build-slib:
	ar -crs $(LDIR)/libfrw.a $(FRW_OBJECTS)