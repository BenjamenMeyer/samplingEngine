#!/bin/bash

COMPILER_NAME="${1}"
COMPILER_VERSION="${2}"

# Read-Only Volume from host containing the source so that we do not need to
# rebuild the containers all the time just to re-run the builds and the test
SOURCE_LOCATION="/home/source/src"

C_COMPILER_NAME="${COMPILER_NAME}"
CXX_COMPILER_NAME="${COMPILER_NAME}"

if [ "${C_COMPILER_NAME}" == "gcc" ]; then
	CXX_COMPILER_NAME="g++"
elif [ "${C_COMPILER_NAME}" == "clang" ]; then
	CXX_COMPILER_NAME="clang++"
fi

C_COMPILER_INFO="${C_COMPILER_NAME}-${COMPILER_VERSION}"
CXX_COMPILER_INFO="${CXX_COMPILER_NAME}-${COMPILER_VERSION}"

# Clean out everything so that it rebuilds properly; protecting against this
# script being run at the root directory.
if [ `pwd` != "/" ]; then
	rm -Rf *
fi


# The below should match the Travis-CI Yaml for the matching environment
cmake -DCMAKE_C_COMPILER=`which ${C_COMPILER_INFO}` -DCMAKE_CXX_COMPILER=`which ${CXX_COMPILER_INFO}` ${SOURCE_LOCATION} && make && make test
