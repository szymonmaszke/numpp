FROM ubuntu:18.04 AS test
LABEL maintainer="a395ux91 (vyzyv) <vyz@protonmail.com>"

COPY . /usr/include/numpp

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
            gcc \
            libeigen3-dev \
            libgsl-dev \
            libomp-dev \
            libgmp-dev \
            cmake \
            bc \
            git && \
    git clone https://github.com/symengine/symengine /tmp/symengine

WORKDIR /tmp/symengine
RUN cmake . && make && make install


FROM ubuntu:18.04 AS deploy
LABEL maintainer="a395ux91 (vyzyv) <vyz@protonmail.com>"

COPY . /usr/include/numpp

RUN apt-get update && \
    apt-get install -y --no-install-recommends gcc
