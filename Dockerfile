FROM golang:1.16-alpine
RUN apk update && apk add --no-cache git
RUN apk add build-base


ENV GOPATH /go
ENV GOBIN /go/bin
ENV CGO_ENABLED 1
WORKDIR /app
RUN mkdir -p /go/bin

COPY go.mod .
# COPY ./go.sum . 
RUN go mod download
RUN go mod verify

COPY . .
RUN make clean
# will run go build and go install internally
RUN make install 
# get the dynamic libs that the go-server depends on and put it on a folder
RUN ./scripts/get-go-server-libs.sh
