FROM ubuntu:latest
MAINTAINER a395ux91 (vyzyv) <vyz@protonmail.com>

COPY . /usr/include/numpp

RUN apt-get update && \
    apt-get install -y \
            gcc \
            libeigen3-dev \
            libgsl-dev \
            libomp-dev \
            libgmp-dev \
            cmake \
            bc \
            git && \
    cd /tmp && git clone https://github.com/symengine/symengine && \
    cd ./symengine && cmake . && make && make install


FROM ubuntu:latest
MAINTAINER a395ux91 (vyzyv) <vyz@protonmail.com>

COPY . /usr/include/numpp

RUN apt-get update && \
    apt-get install -y gcc
