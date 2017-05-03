FROM gcc:latest
MAINTAINER a395ux91 (vyzyv) <vyz@protonmail.com>

COPY differentiation /usr/include/numpp/differentiation
COPY root_finding /usr/include/numpp/root_finding
COPY structures /usr/include/numpp/structures

COPY tests/ /tmp/numpp/tests
