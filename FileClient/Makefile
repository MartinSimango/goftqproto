CC=gcc
CPP=g++
IDIR=include ../include/ ../FilePacket/include ../FileReadWriter/include
ODIR=obj
LDIR=lib
SDIR=src
CFLAGS=$(patsubst %, -I%, $(IDIR)) -std=c++17
LIBNAME=libgocpclient


CLIENT_SOURCES=$(wildcard $(SDIR)/*.cpp)
CLIENT_OBJECTS=$(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(CLIENT_SOURCES))

CLIENT_DLIB_SOURCES = $(CLIENT_OBJECTS) ../FilePacket/lib/*.a ../FileReadWriter/lib/*.a 

CLIENT_DEPS = $(patsubst %, %/*, $(IDIR)) 

all: $(CLIENT_OBJECTS) build

$(CLIENT_OBJECTS): $(ODIR)/%.o : $(SDIR)/%.cpp $(CLIENT_DEPS)
	$(CPP) -c $< -o $@ $(CFLAGS)


build: $(CLIENT_DLIB_SOURCES) $(CLIENT_DEPS)
	ar -crs $(LDIR)/$(LIBNAME).a $(CLIENT_OBJECTS)
	$(CPP) -shared -fPIC -o $(LDIR)/$(LIBNAME).so $(CLIENT_DLIB_SOURCES) $(CFLAGS)


clean:
	rm -r $(ODIR)/*