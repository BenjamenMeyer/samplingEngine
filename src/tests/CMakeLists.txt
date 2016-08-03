# Only Add coverage if the correct build type is active
IF ( CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Coverage")
	# For GCC and Clang
	INCLUDE( CodeCoverage )
	SETUP_TARGET_FOR_COVERAGE(coverage "make && make test && ctest" coverage)
ENDIF()

FIND_PACKAGE(Boost COMPONENTS unit_test_framework REQUIRED)
INCLUDE_DIRECTORIES(${INTERNAL_HEADERS} ${PUBLIC_HEADERS} ${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIR} ${SAMPLING_ENGINE_LIBRARY_DIRl})

ADD_SUBDIRECTORY(engines)
ADD_SUBDIRECTORY(filters)
ADD_SUBDIRECTORY(measurements)
