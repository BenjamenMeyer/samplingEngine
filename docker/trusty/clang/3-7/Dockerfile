FROM ubuntu:14.04
MAINTAINER Benjamen R. Meyer (bm_witness@yahoo.com)

LABEL description="Ubuntu 14.04 LTS (Trusty) CLang 3.7 Test Environment"
ENV COMPILER clang
ENV COMPILER_VERSION 3.7
ENV BUILD_HOME /home/build
ENV BUILD_LOCATION ${BUILD_HOME}/build

RUN apt-get update && apt-get -y upgrade && apt-get -y dist-upgrade
RUN apt-get -y install software-properties-common
RUN apt-get -y install wget
RUN /usr/bin/apt-add-repository ppa:ubuntu-toolchain-r/test
RUN wget -O - http://apt.llvm.org/llvm-snapshot.gpg.key| apt-key add -
RUN /usr/bin/apt-add-repository "deb http://apt.llvm.org/trusty/ llvm-toolchain-trusty-${COMPILER_VERSION} main"
RUN apt-get update
RUN apt-get -y install vim.nox
RUN apt-get -y install build-essential cmake
RUN apt-get -y install clang-${COMPILER_VERSION}
RUN apt-get -y install libboost-test-dev

RUN useradd -m -U -s /bin/bash build
COPY ./docker/tools/build_in_docker.sh ${BUILD_HOME}
WORKDIR ${BUILD_LOCATION}
RUN chown -R build:build ${BUILD_HOME}
USER build
CMD ${BUILD_HOME}/build_in_docker.sh ${COMPILER} ${COMPILER_VERSION}
