FROM ubuntu:18.04 AS deploy
LABEL maintainer="a395ux91 (vyzyv) <vyz@protonmail.com>"

COPY . /usr/include/numpp

RUN apt-get update && \
    apt-get install -y --no-install-recommends gcc \
                                               g++
