FROM scratch 

WORKDIR /app
COPY --from=0 /go/bin/email-service email-service
ENTRYPOINT ["/app/email-service"]
