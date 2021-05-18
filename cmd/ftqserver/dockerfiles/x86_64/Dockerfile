FROM martinsimango/filecopierbase:x86_64_latest

FROM scratch 

EXPOSE 3000

WORKDIR /app
COPY --from=0 /go/bin/ftqserver ftqserver
COPY --from=0 /go-server-dylibs/* /lib/

ENTRYPOINT ["/app/ftqserver"]