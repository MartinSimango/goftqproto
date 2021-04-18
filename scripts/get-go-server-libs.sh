#! /bin/sh

mkdir /go-server-dylibs
ldd  /go/bin/go-server | tr -s '[:blank:]' '\n' | grep '^/' | xargs -I % sh -c 'cp % /go-server-dylibs/;'
