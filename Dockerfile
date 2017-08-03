FROM gcc:latest
MAINTAINER a395ux91 (vyzyv) <vyz@protonmail.com>

COPY . /usr/include/numpp

RUN apt-get update && apt-get install -y libeigen3-dev libgsl-dev libomp-dev
CMD ["/usr/include/numpp/tests/make"]
