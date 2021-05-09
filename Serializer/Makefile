CC=gcc
CPP=g++
IDIR=include
ODIR=obj
LDIR=lib
SDIR=src
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++17
LIBNAME=libserializer

SERIALIZER_SOURCES=$(wildcard $(SDIR)/*.c)
SERIALIZER_OBJECTS=$(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SERIALIZER_SOURCES))

SERIALIZER_DEPS=$(patsubst %, %/*, $(IDIR)) 

SERIALIZER_DLIB_SOURCES=$(SERIALIZER_SOURCES)

build: build-dir $(SERIALIZER_OBJECTS) build-lib 

build-dir:
	mkdir -p $(ODIR)
	mkdir -p $(LDIR)

$(SERIALIZER_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.c $(SERIALIZER_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)

build-lib:
	ar -crs $(LDIR)/$(LIBNAME).a $(SERIALIZER_OBJECTS)
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(SERIALIZER_DLIB_SOURCES) $(CFLAGS)

clean:
	rm -rf $(ODIR)
	rm -rf $(LDIR)