CC=gcc
CPP=g++
IDIR=include
ODIR=obj
LDIR=lib
SDIR=src
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++17
LIBNAME=libpacket

PACKET_SOURCES=$(wildcard $(SDIR)/*.cpp)
PACKET_OBJECTS=$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(PACKET_SOURCES))

PACKET_DEPS=$(patsubst %, %/*, $(IDIR)) 

PACKET_DLIB_SOURCES=$(PACKET_SOURCES)

build: $(PACKET_OBJECTS) build-lib

$(PACKET_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.cpp $(PACKET_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)

build-lib:
	ar -crs $(LDIR)/$(LIBNAME).a $(PACKET_OBJECTS)
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(PACKET_DLIB_SOURCES) $(CFLAGS)

clean:
	rm -r $(ODIR)/*