CC=gcc
CPP=g++
IDIR=include ../include/ ../FilePacket/include ../FileReadWriter/include
ODIR=obj
LDIR=lib
SDIR=src
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++11
LIBNAME=libgocpserver

SERVER_SOURCES=$(wildcard $(SDIR)/*.cpp)
SERVER_OBJECTS=$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SERVER_SOURCES))

SERVER_DEPS = $(patsubst %, %/*, $(IDIR)) 

SERVER_DLIB_SOURCES= $(SERVER_OBJECTS) ../FilePacket/lib/*.a ../FileReadWriter/lib/*.a 

all: $(SERVER_OBJECTS) build 

$(SERVER_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.cpp $(SERVER_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)


build: $(SERVER_DLIB_SOURCES) $(SERVER_DEPS)
	ar -crs $(LDIR)/$(LIBNAME).a $(SERVER_OBJECTS)
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(SERVER_DLIB_SOURCES) $(CFLAGS)

clean:
	rm -r $(ODIR)/*