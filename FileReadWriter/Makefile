CC=gcc
CPP=g++
IDIR=include ../FilePacket/include
ODIR=obj
LDIR=lib
SDIR=src
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++17
LIBNAME=libfrw

FRW_SOURCES=$(wildcard $(SDIR)/*.cpp)
FRW_OBJECTS=$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(FRW_SOURCES))

FRW_DEPS = $(patsubst %, %/*, $(IDIR)) 

FRW_DLIB_SOURCES= $(FRW_SOURCES)

build: $(FRW_OBJECTS) build-lib


$(FRW_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.cpp $(FRW_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)

build-lib: $(FRW_OBJECTS)
	ar -crs $(LDIR)/$(LIBNAME).a $(FRW_OBJECTS) #build the static library
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(FRW_OBJECTS) $(CFLAGS) #build dynamic library


clean:
	rm -rf $(ODIR)/*
	rm -rf $(LDIR)/*