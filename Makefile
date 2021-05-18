
build:
	go build ./...

install: build 
	go install ./...


# --- Docker related ---
docker-build-arm:
	docker build -t martinsimango/goftqprotobase:ARM_latest .
	docker build -f cmd/server/dockerfiles/ARM/DockerFile -t martinsimango/gocpserver:ARM_latest .

docker-build-x86_64:
	docker build -t martinsimango/goftqprotobase:x86_64_latest .
	docker build -f cmd/server/dockerfiles/x86_64/DockerFile  -t martinsimango/gocpserver:x86_64_latest .

docker-push-arm:
	docker push martinsimango/goftqprotobase:ARM_latest
	docker push martinsimango/gocpserver:ARM_latest

docker-push-x86_64:
	docker push martinsimango/goftqprotobase:x86_64_latest
	docker push martinsimango/gocpserver:x86_64_latest

docker-run-server:
	docker run -p 3000:3000 -it -v /:/host/ --env-file .env --name=gocpserver martinsimango/gocpserver

