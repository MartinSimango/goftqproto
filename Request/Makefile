CC=gcc
CPP=g++
IDIR=include ../Serializer/include ../Error/include ../FileReadWriter/include
ODIR=obj
LDIR=lib
SDIR=src
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++17
LIBNAME=libgorequest

REQUEST_SOURCES=$(wildcard $(SDIR)/*.cpp)
REQUEST_OBJECTS=$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(REQUEST_SOURCES))

REQUEST_DLIB_SOURCES = $(REQUEST_SOURCES)

REQUEST_DEPS = $(patsubst %, %/*, $(IDIR)) 

build: build-dir $(REQUEST_OBJECTS) build-lib install

build-dir:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)

$(REQUEST_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.cpp $(REQUEST_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)


build-lib: $(REQUEST_DLIB_SOURCES) $(REQUEST_DEPS)
	ar -crs $(LDIR)/$(LIBNAME).a $(REQUEST_OBJECTS)
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(REQUEST_DLIB_SOURCES) $(CFLAGS)
	
install:
	rm -f /usr/local/lib/$(LIBNAME).so 
	cp $(LDIR)/$(LIBNAME).so /usr/local/lib

clean:
	rm -rf $(ODIR)
	rm -rf $(LDIR)