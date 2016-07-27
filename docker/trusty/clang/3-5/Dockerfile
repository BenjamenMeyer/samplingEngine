FROM ubuntu:14.04
MAINTAINER Benjamen R. Meyer (bm_witness@yahoo.com)

LABEL description="Ubuntu 14.04 LTS (Trusty) Clang 3.5 Test Environment"
ENV COMPILER clang
ENV COMPILER_VERSION 3.5
ENV BUILD_LOCATION /home/build/sampleEngine/build

RUN apt-get update && apt-get -y upgrade && apt-get -y dist-upgrade
RUN apt-get -y install vim.nox
RUN apt-get -y install build-essential cmake
RUN apt-get -y install clang-${COMPILER_VERSION}

RUN useradd -m -U -s /bin/bash build
COPY . /home/build/sampleEngine
RUN if [ ! -d ${BUILD_LOCATION} ]; then mkdir ${BUILD_LOCATION}; else pushd ${BUILD_LOCATION}; rm -Rf *; popd; fi
RUN chown -R build:build /home/build
USER build
WORKDIR /home/build/sampleEngine/build
COPY ./docker/tools/build_in_docker.sh .
CMD ./build_in_docker.sh ${COMPILER} ${COMPILER_VERSION} "../src"
