CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)
PROJECT(SamplingEngine C CXX)
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

MESSAGE("CMake Module Path: ${CMAKE_MODULE_PATH}")

SET(PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../public)
SET(INTERNAL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/../include)

OPTION(ENABLE_CODE_COVERAGE "Enable Code Coverage Information" ON)
IF (${ENABLE_CODE_COVERAGE})
	IF (UNIX)
		# disable optimizations and enable code coverage reports
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -coverage -O0 -g -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
		SET(CMAKE_CFLAGS="${CMAKE_CFLAGS} -g -oO -Wall -W -fprofile-arcs -ftest-coverage")
		SET(CMAKE_LDFLAGS="${CMAKE_LDFLAGS} -fprofile-arcs -ftest-coverage")
	ENDIF()
ENDIF()

INCLUDE(DoxygenTargets)
add_doxygen(
	${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
	OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../doxy
	DOC_TARGET docs
)

INCLUDE_DIRECTORIES(${INTERNAL_HEADERS} ${PUBLIC_HEADERS})
IF(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
ENDIF()

FILE(GLOB_RECURSE SE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
FOREACH(cppFile ${SE_SOURCE})
	#STRING(REGEX MATCH ".*\/tests\/.*" isTestFile ${cppFile})
	IF(${cppFile} MATCHES ".*tests.*")
		LIST(APPEND SE_TEST_SOURCES ${cppFile})
	ENDIF()
ENDFOREACH(cppFile)
IF(DEFINED SE_TEST_SOURCES)
	LIST(REMOVE_ITEM SE_SOURCE ${SE_TEST_SOURCES})
ENDIF()

ADD_LIBRARY(SamplingEngine STATIC ${SE_SOURCE})
IF (${ENABLE_CODE_COVERAGE})
	IF (UNIX)
		TARGET_LINK_LIBRARIES(SamplingEngine gcov)
	ENDIF()
ENDIF()

ENABLE_TESTING()
ADD_SUBDIRECTORY(tests)
