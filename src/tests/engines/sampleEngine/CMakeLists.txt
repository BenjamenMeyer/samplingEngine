ADD_EXECUTABLE(test_basic test_basic.cpp)
TARGET_LINK_LIBRARIES(test_basic ${Boost_LIBRARIES} SamplingEngine)

ADD_TEST(NAME test_basic WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND test_basic)
