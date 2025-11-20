FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

RUN apt update -y && apt upgrade -y
RUN apt install -y build-essential \
    cmake \
    python3 \
    python3-pip \
    python3-venv \
    python3-virtualenv

RUN pip install conan --break-system-packages
