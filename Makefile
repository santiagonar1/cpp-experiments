.PHONY: docker

docker:
	DOCKER_BUILDKIT=1 docker build -t cpp-dev \
	 --platform linux/amd64,linux/arm64 .
