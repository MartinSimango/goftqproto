
build:
	go build ./...

install: build 
	go install ./...


# --- Docker related ---
docker-build-arm:
	#docker build --no-cache -t martinsimango/goftqprotobase:ARM_latest .
	docker build -f cmd/ftqserver/dockerfiles/ARM/Dockerfile -t martinsimango/ftqserver:ARM_latest .

docker-build-x86_64:
	docker build -t martinsimango/goftqprotobase:x86_64_latest .
	docker build -f cmd/ftqserver/dockerfiles/x86_64/Dockerfile  -t martinsimango/ftqserver:x86_64_latest .

docker-push-arm:
	docker push martinsimango/goftqprotobase:ARM_latest
	docker push martinsimango/ftqserver:ARM_latest

docker-push-x86_64:
	docker push martinsimango/goftqprotobase:x86_64_latest
	docker push martinsimango/ftqserver:x86_64_latest

docker-run-server-ARM:
	docker run -p 3000:3000 -it -v /:/host/ --env-file .env --name=ftqserver martinsimango/ftqserver:ARM_latest

docker-run-server-x86_64:
	docker run -p 3000:3000 -it -v /:/host/ --env-file .env --name=ftqserver martinsimango/ftqserver:x86_64_latest