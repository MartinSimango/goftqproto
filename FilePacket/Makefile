CC=gcc
CPP=g++
IDIR=include ../Error/include
ODIR=obj
LDIR=lib
SDIR=src
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++17
LIBNAME=libpacket

PACKET_SOURCES=$(wildcard $(SDIR)/*.cpp)
PACKET_OBJECTS=$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(PACKET_SOURCES))

PACKET_DEPS=$(patsubst %, %/*, $(IDIR)) 

PACKET_DLIB_SOURCES=$(PACKET_SOURCES)

build: build-dir $(PACKET_OBJECTS) build-lib 

build-dir:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)

$(PACKET_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.cpp $(PACKET_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)

build-lib:
	ar -crs $(LDIR)/$(LIBNAME).a $(PACKET_OBJECTS)
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(PACKET_DLIB_SOURCES) $(CFLAGS)

clean:
	rm -rf $(ODIR)/*
	rm -rf $(LDIR)/*