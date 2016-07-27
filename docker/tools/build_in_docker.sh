#!/bin/bash

COMPILER_NAME="${1}"
COMPILER_VERSION="${2}"
SOURCE_LOCATION="${3}"

COMPILER_INFO="${COMPILER_NAME}-${COMPILER_VERSION}"

# The below should match the Travis-CI Yaml for the matching environment
cmake -DCMAKE_CXX_COMPILER=`which ${COMPILER_INFO}` ${SOURCE_LOCATION} && make
