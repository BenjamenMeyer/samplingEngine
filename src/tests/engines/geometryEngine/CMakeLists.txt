ADD_EXECUTABLE(test_geometryEngine_basic test_geometryEngine_basic.cpp)
TARGET_LINK_LIBRARIES(test_geometryEngine_basic ${Boost_LIBRARIES} SamplingEngine)

ADD_TEST(NAME test_geometryEngine_basic WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND test_geometryEngine_basic)
