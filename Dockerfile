FROM gcc:latest
MAINTAINER a395ux91 (vyzyv) <vyz@protonmail.com>

COPY differentiation /usr/include/numpp/differentiation
COPY roots /usr/include/numpp/roots
COPY structures /usr/include/numpp/structures

COPY tests/ /tmp/numpp/tests

# WORKDIR /tmp/numpp/tests/functionality

RUN apt-get update && apt-get install -y libeigen3-dev libgsl-dev libomp-dev
CMD ["make -C /tmp/numpp/tests/functionality"]
