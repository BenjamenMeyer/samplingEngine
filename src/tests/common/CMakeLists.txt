#ADD_SUBDIRECTORY(geometryEngine)
#ADD_SUBDIRECTORY(sampleEngine)

ADD_EXECUTABLE(test_common test_common.cpp)
TARGET_LINK_LIBRARIES(test_common ${Boost_LIBRARIES} SamplingEngine)

ADD_TEST(NAME test_common WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND test_common)
