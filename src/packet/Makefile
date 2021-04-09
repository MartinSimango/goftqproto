CC=gcc
CPP=g++
IDIR=../../include/packet/
ODIR=../../obj/packet
LDIR=../../lib
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++11


PACKET_SOURCES=$(wildcard *.cpp)
PACKET_OBJECTS=$(patsubst %.cpp, $(ODIR)/%.o, $(PACKET_SOURCES))

PACKET_DEPS = $(patsubst %, %/*, $(IDIR)) 

all: $(PACKET_OBJECTS) build-slib

$(PACKET_OBJECTS): $(ODIR)/%.o : %.cpp $(PACKET_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)

build-slib:
	ar -crs $(LDIR)/libpacket.a $(PACKET_OBJECTS)