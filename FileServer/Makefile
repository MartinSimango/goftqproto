CC=gcc
CPP=g++
define IDIR
./include ../Error/include ../Request/include ../Response/include ../FileReadWriter/include ../Serializer/include
endef
ODIR=obj
LDIR=lib
SDIR=src
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++17
LIBNAME=libgocpserver

# TODO check use of OBJECTS files might not even need them

SERVER_SOURCES=$(wildcard $(SDIR)/*.cpp)
SERVER_OBJECTS=$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SERVER_SOURCES))

SERVER_DEPS = $(patsubst %, %/*, $(IDIR)) 

define SERVER_DLIB_SOURCES
$(SERVER_SOURCES) ../Request/src/*.cpp ../Response/src/*.cpp ../FileReadWriter/src/*.cpp ../Error/src/*.cpp
endef

build: build-dir $(SERVER_OBJECTS) build-lib install

build-dir:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)

$(SERVER_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.cpp $(SERVER_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)


build-lib: $(SERVER_DLIB_SOURCES) $(SERVER_DEPS)
	ar -crs $(LDIR)/$(LIBNAME).a $(SERVER_OBJECTS)
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(SERVER_DLIB_SOURCES) $(CFLAGS)

install:
	rm -f /usr/local/lib/$(LIBNAME).so 
	cp $(LDIR)/$(LIBNAME).so /usr/local/lib

clean:
	rm -rf $(ODIR)
	rm -rf $(LDIR)