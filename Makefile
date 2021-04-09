CC=gcc
CPP=g++
CFLAGS=-std=c++11
SUBDIRS := $(wildcard src/*)

all: $(SUBDIRS) client server
$(SUBDIRS):
	$(MAKE) -C $@

.PHONY: all $(SUBDIRS)

client: 
	$(CPP) -o client lib/libgocpclient.a lib/libpacket.a lib/libfrw.a 

server:
	$(CPP) -o server lib/libgocpserver.a lib/libpacket.a lib/libfrw.a