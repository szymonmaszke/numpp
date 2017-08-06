FROM gcc:latest
MAINTAINER a395ux91 (vyzyv) <vyz@protonmail.com>

COPY . /usr/include/numpp

RUN apt-get update && \
    add-apt-repository ppa:symengine/ppa && \
    apt-get install -y \
            libeigen3-dev \
            libgsl-dev \
            libomp-dev \
            libsymengine-dev
