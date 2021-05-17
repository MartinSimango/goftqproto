CC=gcc
CPP=g++
IDIR=include ../Serializer/include ../Error/include ../FileReadWriter/include ../Request/include
ODIR=obj
LDIR=lib
SDIR=src
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++17
LIBNAME=libgoresponse


RESPONSE_SOURCES=$(wildcard $(SDIR)/*.cpp)
RESPONSE_OBJECTS=$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(RESPONSE_SOURCES))

RESPONSE_DLIB_SOURCES = $(RESPONSE_SOURCES)

RESPONSE_DEPS = $(patsubst %, %/*, $(IDIR)) 

build: build-dir $(RESPONSE_OBJECTS) build-lib install

build-dir:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)

$(RESPONSE_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.cpp $(RESPONSE_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)


build-lib: $(RESPONSE_DLIB_SOURCES) $(RESPONSE_DEPS)
	ar -crs $(LDIR)/$(LIBNAME).a $(RESPONSE_OBJECTS)
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(RESPONSE_DLIB_SOURCES) $(CFLAGS)
	
install:
	rm -f /usr/local/lib/$(LIBNAME).so 
	cp $(LDIR)/$(LIBNAME).so /usr/local/lib

clean:
	rm -rf $(ODIR)
	rm -rf $(LDIR)