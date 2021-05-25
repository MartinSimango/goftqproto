#! /bin/sh

mkdir /ftqserver-dylibs
ldd  /go/bin/ftqserver | tr -s '[:blank:]' '\n' | grep '^/' | xargs -I % sh -c 'cp % /ftqserver-dylibs/;'
