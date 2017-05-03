FROM base/devel
MAINTAINER a395ux91 (vyzyv) <vyz@protonmail.com>

COPY differentiation/ /usr/include/numpp/
COPY root_finding/ /usr/include/numpp/
COPY structures/ /usr/include/numpp/

COPY tests/ /tmp/numpp/tests/

RUN pacman -Syyu --noconfirm
RUN pacman -S --noconfirm git
RUN pacman -S --noconfirm python

#NEWEST GCC FROM GIT

RUN useradd --no-create-home --shell=/bin/bash user
RUN mkdir -p /tmp/gcc-git && chown user /tmp/gcc-git
RUN echo "user ALL = NOPASSWD: /usr/bin/pacman" >> /etc/sudoers
USER user
RUN cd /tmp/gcc-git && git clone https://aur.archlinux.org/gcc-git.git && cd /tmp/gcc-git/gcc-git && makepkg -sric --noconfirm  && rm -rf /tmp/gcc-git

USER root
