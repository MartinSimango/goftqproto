FROM martinsimango/goftqprotobase:ARM_latest

FROM scratch 

EXPOSE 3000

WORKDIR /app
COPY --from=0 /go/bin/ftqserver ftqserver
COPY --from=0 /ftqserver-dylibs/* /lib/

ENTRYPOINT ["/app/ftqserver"]
