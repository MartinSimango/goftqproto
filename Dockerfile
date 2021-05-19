FROM golang:1.16-alpine
RUN apk update && apk add --no-cache git
RUN apk add build-base

#intall dependencies
RUN git clone https://github.com/MartinSimango/GoCPPError.git
RUN cd GoCPPError && make clean build install-docker && cd ..

RUN git clone https://github.com/MartinSimango/ftqproto.git 
RUN cd ftqproto && make clean build install-docker && cd ..

ENV GOPATH /go
ENV GOBIN /go/bin
ENV CGO_ENABLED 1
WORKDIR /app
RUN mkdir -p /go/bin

COPY go.mod .
COPY go.sum . 
RUN go mod download
RUN go mod verify

COPY . .
RUN go build ./...
RUN go install ./...

# get the dynamic libs that the go-server depends on and put it on a folder
RUN ./scripts/get-go-server-libs.sh
