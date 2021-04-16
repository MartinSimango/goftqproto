CC=gcc
CPP=g++
ODIR=obj
IDIR=FileClient/include include FileReadWriter/include FilePacket/include
LDIR=FileClient/lib
SUBDIRS := $(wildcard src/*)
CFLAGS=$(patsubst %, -I%, $(IDIR)) $(patsubst %, -L%, $(LDIR)) -std=c++17


all: $(SUBDIRS)  client server
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)


client: client_test.cpp 
	 $(CPP) -o client_2 client_test.cpp  $(CFLAGS) -lgocpclient

server: server_test.cpp lib/libgocpserver.so
	  $(CPP) -o server_2 server_test.cpp  $(CFLAGS) -lgocpserver


# client: lib/libgocpclient.a lib/libpacket.a lib/libfrw.a 
# 	$(CPP) -o client lib/libgocpclient.a lib/libpacket.a lib/libfrw.a 

# server: lib/libgocpserver.a lib/libpacket.a lib/libfrw.a 
# 	$(CPP) -o server lib/libgocpserver.a lib/libpacket.a lib/libfrw.a

# client-d: lib/libgocpclient.so lib/libpacket.so lib/libfrw.so 
# 	$(CPP) -o client lib/libgocpclient.so lib/libpacket.so lib/libfrw.so

# server-d: lib/libgocpserver.so lib/libpacket.so lib/libfrw.so 
# 	$(CPP) -o server lib/libgocpserver.so lib/libpacket.so lib/libfrw.so

clean:
	rm -r $(ODIR)/*/*.o